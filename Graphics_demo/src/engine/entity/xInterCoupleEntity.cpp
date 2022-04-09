#include "xInterCoupleEntity.h"

xInterCoupleEntity::xInterCoupleEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterCoupleEntity::~xInterCoupleEntity()
{
}

void xInterCoupleEntity::setText(const QString &text)
{
	if (text == m_text)
		return;

	prepareGeometryChange();
	m_text = text;
	update();
}

void xInterCoupleEntity::bindEntity1(xEntity *e)
{
	if (e == m_entity1)
		return;

	m_entity1 = e;
}

void xInterCoupleEntity::bindEntity2(xEntity *e)
{
	if (e == m_entity2)
		return;

	m_entity2 = e;
}
