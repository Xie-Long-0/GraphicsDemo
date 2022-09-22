#pragma once

#include <QList>
#include <QGraphicsObject>
#include "xTypeDef.h"
#include "xGraphicView.h"

/**
 * @brief 基于QGraphicsObject，带有画笔、样式和信号槽的图元虚基类
*/
class xEntity : public QGraphicsObject
{
	Q_OBJECT

public:
	enum EntityType {
		ET_Unknown = UserType,
		// 不带范围的图元
		ET_Entity_Start,
		ET_Line,
		ET_Circle,
		ET_Arc,
		ET_Point,
		ET_Entity_End,
		// 带范围的图元
		ET_Region_Start,
		ET_RegLine,
		ET_RegCircle,
		ET_RegArc,
		ET_RegPoint,
		ET_RegRect,
		ET_Region_End,
		// 绑定单个图元
		ET_InterSingle_Start,
		ET_InterLine,
		ET_InterCircle,
		ET_InterArc,
		ET_InterPoint,
		ET_InterSingle_End,
		// 绑定两个图元
		ET_InterCouple_Start,
		ET_InterLineAndLine,
		ET_InterLineAndCircle,
		ET_InterLineAndArc,
		ET_InterLineAndPoint,
		ET_InterCircleAndCircle,
		ET_InterCircleAndArc,
		ET_InterCircleAndPoint,
		ET_InterPointAndPoint,
		ET_InterCouple_End
	};
	Q_ENUM(EntityType)

	Q_DISABLE_COPY(xEntity)
	explicit xEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xEntity() = default;
	
	/**
	 * @brief 移动图元
	 * @param delta 移动增量，需传入scene坐标中的值
	*/
	virtual void moveBy(const QPointF &delta) = 0;
	// 返回图元的绘画控制点
	virtual QList<QPointF> controlPoints() const noexcept = 0;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	virtual void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) = 0;
	// 判断是否是控制点，需传入scene坐标中的值
	virtual bool isCtrlPoint(const QPointF &p) const = 0;

	xDef::EntityStatus status() const noexcept { return m_status; }
	void setStatus(xDef::EntityStatus status) noexcept { m_status = status; }
	QPen pen() const noexcept { return m_pen; }
	void setPen(const QPen &pen);
	xDef::Style style() const noexcept { return m_style; }
	void setStyle(xDef::Style style);
	QString name() const noexcept { return m_name; }
	void setName(const QString &name) { m_name = name; }

	inline xEntity* parentEntity() const;

	bool isThisVisible() const noexcept { return isVisible() && opacity() > 0; }
	bool isMovable() const noexcept { return (flags() & ItemIsMovable); }
	bool isSelectable() const noexcept { return (flags() & ItemIsSelectable); }
	bool hasChild() const noexcept { return m_hasChild; }

	bool needCalculate() const noexcept { return m_needCalc; }
	void setNeedCalcFlag(bool flag) noexcept { m_needCalc = flag; }

public slots:
	// 通过透明度设置此图元的可见性，不影响children的可见性
	inline void setThisVisible(bool visible) noexcept;
	inline void showThis() noexcept { setThisVisible(true); }
	inline void hideThis() noexcept { setThisVisible(false); }
	inline void setMovable(bool b) noexcept;
	inline void setSelectable(bool b) noexcept;

signals:
	void selectedChanged(bool selected);
	void cursorChanged(const QCursor &newCursor);
	void flagsChanged(const GraphicsItemFlags &newFlags);
	// 位置改变信号，由moveBy函数发送
	void posChanged(const QPointF &delta);
	// 形状改变信号
	void shapeChanged();
	// 通知关联图形进行计算
	void requestCalc();

protected:
	// 用于处理基类QGraphicsItem传递的改变，发送相应信号
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	// 获取视图的缩放系数
	inline qreal viewScaleFactor() const noexcept;

	QString m_name;	// 图元的名称
	QPen m_pen;
	xDef::Style m_style = xDef::S_NoStyle;
	xDef::EntityStatus m_status = xDef::ES_NotMeasured;
	xGraphicView *m_view = nullptr;
	bool m_needCalc = false;
	bool m_hasChild = false;

private:
	inline void init() noexcept;
};

inline void xEntity::init() noexcept
{
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	// 忽略parent的透明度，以实现parent不可见而children可见
	setFlag(ItemIgnoresParentOpacity);
	setAcceptHoverEvents(true);
}

inline void xEntity::setThisVisible(bool visible) noexcept
{
	if (visible)
		setOpacity(1.0);
	else
		setOpacity(0);
}

inline void xEntity::setMovable(bool b) noexcept
{
	if (b)
		setFlag(ItemIsMovable, true);
	else
		setFlag(ItemIsMovable, false);
}

inline void xEntity::setSelectable(bool b) noexcept
{
	if (b)
		setFlag(ItemIsSelectable, true);
	else
		setFlag(ItemIsSelectable, false);
}

inline qreal xEntity::viewScaleFactor() const noexcept
{
	if (m_view == nullptr) return 1.0;
	return m_view->scaleFactor();
}

inline xEntity *xEntity::parentEntity() const
{
	if (auto e = QGraphicsItem::parentItem(); e != nullptr && e->type() > xEntity::ET_Unknown)
		return static_cast<xEntity *>(e);
	return nullptr;
}
