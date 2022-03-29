# GraphicsDemo
一个基于Qt GraphicsView框架的绘图框架。


### 主要功能

可以选择手动绘画线段、圆、圆弧等操作，并对图元进行移动和修改等操作。

### 框架结构

整体框架主要由Entity图元类、GraphicView类、Action操作类及界面相关部分组成。

#### Entity图元类

继承于QGraphicsItem的自定义图元。

#### GraphicView类

继承于QGraphicsView的视图类，负责绘图及管理动作事件。

#### Action操作类

用于定义和操作绘图动作。

