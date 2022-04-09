#pragma once

#include <QList>
#include <QGraphicsObject>
#include "xTypeDef.h"
#include "xStyle.h"
#include "xGraphicView.h"

/**
 * @brief 基于QGraphicsItem的带有画笔和样式的图元虚基类
*/
class xEntity : public QGraphicsObject
{
	Q_OBJECT

public:
	enum {
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
		ET_Region_End
	};

	Q_DISABLE_COPY(xEntity)
	explicit xEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xEntity() = default;

	// 移动图元，delta为移动增量
	virtual void moveBy(const QPointF &delta) = 0;
	// 返回图元的绘画控制点
	virtual QList<QPointF> controlPoints() const = 0;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 图元上的控制点
	 * @param movedPt 移动后的点位置
	*/
	virtual void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) = 0;
	// 判断是否是控制点
	virtual bool isCtrlPoint(const QPointF &p) const = 0;

	QPen pen() const { return m_pen; }
	void setPen(const QPen &pen);
	xStyle::Style style() const { return m_style; }
	void setStyle(xStyle::Style style);

signals:
	// 位置改变信号，由moveBy函数发送
	void posChanged(const QPointF &delta);
	// 形状改变信号
	void shapeChanged();
	void selectedChanged(bool selected);
	void cursorChanged(const QCursor &newCursor);
	void flagsChanged(const GraphicsItemFlags &newFlags);

protected:
	// 用于处理基类QGraphicsItem传递的改变，发送相应信号
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
	// 获取视图的缩放系数
	inline qreal viewScaleFactor() const;

	QPen m_pen;
	xStyle::Style m_style = xStyle::NoStyle;
	xGraphicView *m_view = nullptr;

private:
	inline void init();
};

inline void xEntity::init()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}

inline qreal xEntity::viewScaleFactor() const
{
	// 通过view的转换矩阵获取缩放系数，m11存放的值表示缩放倍数
	return m_view->transform().m11();
}
