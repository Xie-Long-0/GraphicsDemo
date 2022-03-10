#include "xActionDefault.h"
#include <QMouseEvent>

xActionDefault::xActionDefault(xGraphicView *view, QObject *parent)
	: xActionInterface(view, parent, xDef::AT_Default)
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
