# 架构审查与改进建议（GraphicsDemo）

## 当前架构合理性（结论）

项目目前采用 **UI / View / Action / Entity / Processing** 的分层思路，作为 CAD-lite 原型是合理的：

- `Entity` 负责图元建模与渲染，边界清晰。
- `Action` 负责交互状态机，能够支持不同绘制流程。
- `xGraphicView` 负责事件分发与场景管理。
- `processing/RecognizeHandler` 预留了“测量/识别”能力入口。

这个基础分层可以继续演进成可维护的 CAD 业务架构。

---

## 关键问题与改进优先级

## P0（建议优先改）

### 1) `MainWindow` 过度编排，存在明显重复与耦合

`onDrawLine/onDrawCircle/onDrawArc/...` 基本重复：

- 创建 `OperationWidget`
- 切换右侧 UI
- 创建 Action
- 绑定 confirm/cancel/next/calc

这导致新增一个图元功能就要复制一整段 UI + 连接逻辑，后续维护风险较高。

**改进建议**

- 提取统一入口：`startAction(ActionFactory, OperationMode)`。
- 建立 `ActionDescriptor`（名称、工厂函数、是否支持calc、是否支持next）。
- 将按钮与 descriptor 映射后统一启动，减少重复槽函数。

### 2) 内存管理策略混用（`delete` / `deleteLater` / QObject 父子）

当前既有 `delete`（如 `xGraphicView::finishAction`），也有 `deleteLater`（如 `xActionDrawLine::cancel`），并且 Action 不是 QObject 层级托管对象，容易出现生命周期不一致。

**改进建议**

- 二选一：
  1. Action 全部改成 QObject 派生并统一 parent 托管；或
  2. 保持非 QObject，但使用 `std::unique_ptr` 统一所有权（推荐）。
- 明确约束：Action 内持有的图元释放策略必须一致（立即释放或延迟释放不可混用）。

### 3) 交互与业务耦合在 `xGraphicView`

`xGraphicView` 同时处理：

- 输入事件分发
- 缩放平移
- 删除策略
- Action 生命周期

导致 View 成为“超大类”，难以单测与演进。

**改进建议**

- 引入 `EditorController`（或 `CommandController`）：
  - 管理当前 action、默认 action、撤销重做命令栈。
  - `xGraphicView` 仅保留 View 职责（坐标映射 + 显示）。
- 删除逻辑下沉到 `SceneService` 或 `EntityRepository`。

---

## P1（中期优化）

### 4) 缺失“文档模型（Document Model）”层

目前 scene item 既是渲染对象又是业务对象。做 CAD 时，后续会碰到：

- 文件保存/加载（DXF/自定义格式）
- 约束、标注、图层
- 批量计算与离屏处理

缺失模型层会让这些能力与 Qt 图形对象强耦合。

**改进建议**

- 增加 `Document` / `EntityModel`（纯数据）层。
- `QGraphicsItem` 仅作为 ViewModel/Renderer。
- 使用 id 绑定 model 与 item，支持序列化与回放。

### 5) Action 状态机实现分散，缺少统一约束

Action 以 `m_status` + switch 驱动，能用但易分叉，不同 Action 的状态语义可能漂移。

**改进建议**

- 定义统一状态机协议：`Idle -> Preview -> ReadyToCommit -> Committed/Cancelled`。
- 抽象基类钩子：`onStart/onPreview/onCommit/onCancel`。
- 对多步 action（如圆弧）引入小型状态表，避免分散 if/switch。

### 6) 测量能力是模拟实现，线程模型仍需正规化

`RecognizeHandler` 中通过 `msleep` 模拟计算，后续接真实算法时需要完整任务调度。

**改进建议**

- 引入任务接口 `IMeasureTask` 与 `TaskDispatcher`（线程池/QThreadPool）。
- 统一回调协议：成功/失败/超时/取消。
- 禁止在 UI 线程里做可阻塞操作。

---

## P2（长期演进）

### 7) 枚举 type 判定过多，可逐步转向能力接口

目前通过 `type()` 区间判断（Region/InterSingle/InterCouple）。初期可行，但扩展新类型时代码会散落多个分支。

**改进建议**

- 增加能力接口（例如 `IResizableRegion`、`ICalculable`、`IBindableEntity`）。
- 让“行为”替代“类型区间判断”。

### 8) 缺少命令系统（Undo/Redo）

CAD 常用“每一步可撤销”，当前 Action 直接操作 scene item，不利于构建历史栈。

**改进建议**

- 引入 Command 模式：`CreateEntityCommand`、`MoveEntityCommand`、`ModifyCtrlPointCommand`。
- Action 只负责收集交互参数，提交 command 到命令栈执行。

### 9) 可测试性不足

几何计算、状态迁移、删除规则都在 Qt 事件路径中，单元测试难写。

**改进建议**

- 把几何与规则抽到纯 C++ service。
- 为 action 状态机与实体操作写无 UI 的单元测试。

---

## 建议的目标架构（简版）

- **UI 层**：MainWindow / Widgets（仅展示与用户意图上报）
- **Controller 层**：ActionController + CommandStack + SelectionManager
- **Domain 层**：DocumentModel + GeometryServices + MeasureServices
- **Infra 层**：QtGraphicsAdapter（Model<->QGraphicsItem 映射）+ Persistence

这样可以在保留 Qt GraphicsView 的前提下，提高可扩展性与工程可维护性。

---

## 落地路线（3 个迭代）

1. **迭代1（低风险重构）**
   - 抽取 `startAction()`，消除 MainWindow 重复代码。
   - 统一 Action 生命周期管理策略。
   - `xGraphicView` 删除逻辑独立为 helper/service。

2. **迭代2（能力建设）**
   - 引入 Command 栈，先覆盖“创建/删除/移动”。
   - 规范 Action 状态机接口。

3. **迭代3（架构升级）**
   - 增加 DocumentModel，建立 model-item 映射。
   - 测量任务异步化（线程池 + 回调协议）。

