#include "xActionInterface.h"
#include "xGraphicView.h"
#include <QMouseEvent>

xActionInterface::xActionInterface(xGraphicView *view, xDef::ActionType type)
	: m_view(view)
	, m_type(type)
{
	if (view) m_scene = view->scene();
}

xActionInterface::~xActionInterface()
{
}

QPointF xActionInterface::pointMapToScene(QMouseEvent *e) const
{
	if (m_view == nullptr || e == nullptr)
		return QPointF();
	return m_view->mapToScene(e->pos());
}
