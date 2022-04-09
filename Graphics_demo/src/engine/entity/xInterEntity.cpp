#include "xInterEntity.h"

xInterEntity::xInterEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterEntity::~xInterEntity()
{
}

void xInterEntity::setText(const QString &text)
{
	if (text == m_text)
		return;

	prepareGeometryChange();
	m_text = text;
	update();
}

void xInterEntity::setEntity(xEntity *e)
{
	if (e == m_entity)
		return;

	m_entity = e;
}

void xInterEntity::setEntity2(xEntity *e)
{
	if (e == m_entity2)
		return;

	m_entity2 = e;
}
