#pragma once

#include <QGraphicsItem>
#include "xTypeDef.h"
#include "xStyle.h"
#include "xEntity.h"

class xCircle : public QGraphicsItem, public xEntity
{
public:
	explicit xCircle(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const xCircleData &circle, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &center, qreal radius, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(qreal cx, qreal cy, qreal radius, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, xGraphicView *view, QGraphicsItem *parent = nullptr);

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

	void setPen(const QPen &pen) override;
	void setStyle(xStyle::Style style) override;

	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	inline void init();

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
