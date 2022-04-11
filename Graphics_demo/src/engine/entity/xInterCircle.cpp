#include "xInterCircle.h"

xInterCircle::xInterCircle(xGraphicView *view, QGraphicsItem *parent)
	:xInterSingleEntity(view, parent)
{
}

xInterCircle::xInterCircle(xEntity *item, xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(item, view, parent)
{
}

xInterCircle::~xInterCircle()
{
}

int xInterCircle::type() const
{
	return Type;
}

void xInterCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QRectF xInterCircle::boundingRect() const
{
	return QRectF();
}

QPainterPath xInterCircle::shape() const
{
	return QPainterPath();
}

void xInterCircle::onEntityChanged()
{
}
