#include "xActionInterface.h"
#include "xGraphicView.h"
#include <QMouseEvent>

xActionInterface::xActionInterface(xGraphicView *view, QObject *parent, xDef::ActionType type)
	: QObject(parent)
	, m_view(view)
	, m_type(type)
{
	if (view) m_scene = view->scene();
}

bool xActionInterface::isFinished() const
{
	if (m_status >= xDef::S_ActionFinished)
		return true;
	return false;
}

void xActionInterface::mouseDoubleClickEvent(QMouseEvent *e)
{
}

QPointF xActionInterface::pointMapToScene(QMouseEvent *e) const
{
	if (m_view == nullptr || e == nullptr)
		return QPointF();
	return m_view->mapToScene(e->pos());
}
