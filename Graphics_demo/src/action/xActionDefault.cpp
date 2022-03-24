#include "xActionDefault.h"
#include <QMouseEvent>

xActionDefault::xActionDefault(xGraphicView *view)
	: xActionInterface(view, xDef::AT_Default)
{
}

xActionDefault::~xActionDefault()
{
}

void xActionDefault::mousePressEvent(QMouseEvent *e)
{
	
}

void xActionDefault::mouseMoveEvent(QMouseEvent *e)
{
}

void xActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
}
