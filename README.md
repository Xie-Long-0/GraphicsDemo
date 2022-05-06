# GraphicsDemo

一个基于[Qt Graphics View Framework](https://doc.qt.io/qt-5/graphicsview.html) 的绘图框架。

### 主要功能

可以手动绘画线段、圆、圆弧等图形，并对图形进行移动和修改等操作。

### 框架结构

本框架基于`Qt GraphicsView`框架，主要由 **`Entity` 图元类** 、**`GraphicView` 视图类**、**`Action` 操作类**及界面相关部分组成。

在`Qt GraphicsView`框架中存在3个坐标系，即Scene场景坐标系，View视图坐标系，Item内部坐标系。为了操作方便，本框架中图元的坐标全部使用Scene中的坐标，在进行Item交互时需要将View的坐标转换成Scene中的坐标，并替换图元的移动操作，避免使用Transform进行变换。

*由View转换到Scene的坐标使用View的`mapToScene`函数。*

#### Entity图元类

继承于`QGraphicsObject`的自定义图元，带有信号槽。

Entity图元又分为基于`xEntity`的基本图元、基于`xRegionEntity`的带范围图元、基于`xInterSingleEntity`的单关联图元和基于`xInterCoupleEntity`的双关联图元。

继承关系如下：

```c
                  QGraphicsObject
                         |
                         V
                      xEntity
                         |
      +------------------+---------------------+
      |                  |                     |
      V                  V                     V
xRegionEntity    xInterSingleEntity    xInterCoupleEntity
```

- ##### xEntity Class

带有画笔、预定义样式和信号槽的图元虚基类，定义了所有自定义图元的一些公共接口。

- ##### xRegionEntity Class

基于`xEntity`，带有范围的图元。添加了笔刷。

- ##### xInterSingleEntity Class

基于`xEntity`，关联一个`xEntity`或`xRegionEntity`的扩展图元。

- ##### xInterCoupleEntity Class

基于`xEntity`，关联一个`xEntity`或`xRegionEntity`的扩展图元。

#### GraphicView类

继承于`QGraphicsView`的视图类，负责绘图及管理动作事件。

#### Action操作类

用于定义和操作绘图动作。

Action分为`xActionDefault`默认操作类、`xActionInterface`无预览操作类和`xActionPreviewInterface`预览操作类。

- ##### xActionDefault

负责执行对图元的移动、拉伸等操作，在没有其它Action执行时执行此类。

- ##### xActionInterface Class

用于无需预览层的操作类的基类。

- ##### xActionPreviewInterface Class

基于`xActionInterface`，用于需要预览层的操作类的基类。添加了确认和取消的操作。
