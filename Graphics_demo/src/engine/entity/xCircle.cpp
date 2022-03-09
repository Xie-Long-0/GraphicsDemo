#include "xCircle.h"

xCircle::xCircle(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
}

int xCircle::type() const
{
	return Type;
}
