#pragma once

#include <QGraphicsItem>
#include "xTypeDef.h"
#include "xStyle.h"

class xCircle : public QGraphicsItem
{
public:
	explicit xCircle(QGraphicsItem *parent = nullptr);
	xCircle(const xCircleData &circle, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &center, qreal radius, QGraphicsItem *parent = nullptr);
	xCircle(qreal cx, qreal cy, qreal radius, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = xDef::ET_Circle };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	xCircleData circleData() const;
	void setCircle(const xCircleData &circle);
	void setCircle(const QPointF &center, qreal radius);

	QPointF center() const;
	void setCenter(const QPointF &center);
	qreal radius() const { return m_circle.radius(); }
	void setRadius(qreal radius);

	QPen pen() const { return m_pen; }
	void setPen(const QPen &pen);
	xStyle::Style style() const { return m_style; }
	void setStyle(xStyle::Style style);

protected:
	inline void init();
	// 获取视图的缩放系数
	qreal viewScaleFactor() const;

	xStyle::Style m_style = xStyle::NoStyle;
	QPen m_pen;
	xCircleData m_circle;

private:
	Q_DISABLE_COPY(xCircle)
};

inline void xCircle::init()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}
