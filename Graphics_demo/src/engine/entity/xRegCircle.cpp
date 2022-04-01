#include "xRegCircle.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xRegCircle::xRegCircle(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

xRegCircle::xRegCircle(const xCircleData &circle, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

xRegCircle::xRegCircle(const QPointF &center, qreal radius, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

xRegCircle::xRegCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

int xRegCircle::type() const
{
	return Type;
}

void xRegCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QRectF xRegCircle::boundingRect() const
{
	return QRectF();
}

QPainterPath xRegCircle::shape() const
{
	return QPainterPath();
}

void xRegCircle::setCircle(const QPointF &center, qreal radius)
{
}

void xRegCircle::setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3)
{
}

void xRegCircle::setCenter(const QPointF &center)
{
}

void xRegCircle::setRadius(qreal radius)
{
}

void xRegCircle::setPt1(const QPointF &p)
{
}

void xRegCircle::setPt2(const QPointF &p)
{
}

void xRegCircle::setPt3(const QPointF &p)
{
}

void xRegCircle::moveBy(const QPointF &delta)
{
}

QList<QPointF> xRegCircle::controlPoints() const
{
	return QList<QPointF>();
}

void xRegCircle::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
}

bool xRegCircle::isCtrlPoint(const QPointF &p) const
{
	return false;
}

void xRegCircle::changeEdgeByPoint(const QPointF &p)
{
}

bool xRegCircle::isRegionEdge(const QPointF &p) const
{
	return false;
}
