#include "xActionDefault.h"
#include <QMouseEvent>

xActionDefault::xActionDefault(QGraphicsScene *scene, xGraphicView *view, QObject *parent)
	: xActionInterface(scene, view, parent, xDef::AT_Default)
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
