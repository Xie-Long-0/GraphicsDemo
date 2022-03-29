#include "xRegLine.h"

xRegLine::xRegLine(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

int xRegLine::type() const
{
	return Type;
}

void xRegLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QRectF xRegLine::boundingRect() const
{
	return QRectF();
}

QPainterPath xRegLine::shape() const
{
	return QPainterPath();
}

void xRegLine::setRegWidth(qreal w)
{
}

void xRegLine::setLine(const QLineF &line)
{
}

void xRegLine::setPt1(const QPointF &p)
{
}

void xRegLine::setPt2(const QPointF &p)
{
}

QList<QPointF> xRegLine::controlPoints() const
{
	return QList<QPointF>();
}

void xRegLine::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
}

bool xRegLine::isCtrlPoint(const QPointF &p) const
{
	return false;
}
