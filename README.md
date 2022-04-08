# GraphicsDemo

一个基于Qt GraphicsView框架的绘图框架。


### 主要功能

可以手动绘画线段、圆、圆弧等操作，并对图元进行移动和修改等操作。

### 框架结构

整体框架主要由Entity图元类、GraphicView类、Action操作类及界面相关部分组成。

在Qt的QGraphicsView框架中存在3个坐标系，即Scene场景坐标系，View视图坐标系，Item内部坐标系。在本框架中基本只关注Scene中的坐标系，所以在操作View和Item坐标的时候都先把对应坐标转换成在Scene中的坐标。

由View操作Scene时使用View的mapToScene函数转换坐标，在Item中设置坐标时使用Item的mapFromScene函数转换坐标。

#### Entity图元类

继承于QGraphicsItem的自定义图元。

Entity图元又分为基于xEntity的基本图元和基于xRegionEntity的带范围图元，而xRegionEntity也是从xEntity派生而来的。

#### GraphicView类

继承于QGraphicsView的视图类，负责绘图及管理动作事件。

#### Action操作类

用于定义和操作绘图动作。

