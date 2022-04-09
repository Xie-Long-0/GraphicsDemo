#include "xInterSingleEntity.h"

xInterSingleEntity::xInterSingleEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterSingleEntity::xInterSingleEntity(xEntity *item, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_entity(item)
{
}

xInterSingleEntity::~xInterSingleEntity()
{
}

void xInterSingleEntity::setText(const QString &text)
{
}

void xInterSingleEntity::bindEntity(xEntity *e)
{
}

QList<QPointF> xInterSingleEntity::controlPoints() const
{
	return QList<QPointF>();
}

void xInterSingleEntity::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
}

bool xInterSingleEntity::isCtrlPoint(const QPointF &p) const
{
	return false;
}
