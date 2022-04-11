#include "xInterSingleEntity.h"

xInterSingleEntity::xInterSingleEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterSingleEntity::xInterSingleEntity(xEntity *item, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
	bindEntity(item);
}

xInterSingleEntity::~xInterSingleEntity()
{
	if (m_entity)
	{
		disconnect(m_entity);
	}
}

void xInterSingleEntity::setText(const QString &text)
{
	if (text == m_text)
		return;

	prepareGeometryChange();
	m_text = text;
	update();
}

void xInterSingleEntity::setBindPoint(const QPointF &p)
{
	if (p == m_bindPoint)
		return;

	prepareGeometryChange();
	m_bindPoint = p;
	update();
}

void xInterSingleEntity::setAnchorPoint(const QPointF &p)
{
	if (p == m_anchorPoint)
		return;

	prepareGeometryChange();
	m_anchorPoint = p;
	update();
}

void xInterSingleEntity::setShiftDistance(qreal dist)
{
	if (qFuzzyCompare(dist, m_shiftDist))
		return;

	prepareGeometryChange();
	m_shiftDist = dist;
	update();
}

void xInterSingleEntity::bindEntity(xEntity *e)
{
	if (e == m_entity)
		return;

	if (m_entity)
	{
		disconnect(m_entity);
	}

	if (e)
	{
		connect(e, &xEntity::shapeChanged, this, &xInterSingleEntity::onEntityChanged);
		connect(e, &xEntity::posChanged, this, &xInterSingleEntity::onEntityMoved);
		connect(e, &xEntity::destroyed, this, &xEntity::deleteLater);
	}

	m_entity = e;
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

void xInterSingleEntity::onEntityMoved(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_bindPoint += delta;
	update();
}
