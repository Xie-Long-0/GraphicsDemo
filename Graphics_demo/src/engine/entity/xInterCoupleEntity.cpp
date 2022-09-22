#include "xInterCoupleEntity.h"

xInterCoupleEntity::xInterCoupleEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterCoupleEntity::xInterCoupleEntity(xEntity *item1, xEntity *item2, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
	bindEntity1(item1);
	bindEntity2(item2);
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
	m_lastFactor = -1;	// 文本改变时重新计算文本大小
	update();
}

void xInterCoupleEntity::setBindPoint1(const QPointF &p)
{
	if (p == m_bindPoint1)
		return;

	prepareGeometryChange();
	m_bindPoint1 = p;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint1, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint1.x(), m_bindPoint1.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint1.x(), -m_bindPoint1.y());
	update();
}

void xInterCoupleEntity::setBindPoint2(const QPointF &p)
{
	if (p == m_bindPoint2)
		return;

	prepareGeometryChange();
	m_bindPoint2 = p;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint2, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint2.x(), m_bindPoint2.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint2.x(), -m_bindPoint2.y());
	update();
}

void xInterCoupleEntity::setAnchorPoint(const QPointF &p)
{
	if (p == m_anchorPoint)
		return;

	prepareGeometryChange();
	m_anchorPoint = p;
	//m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint, m_anchorPoint);
	//m_transform.reset();
	//m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	//m_transform.rotateRadians(m_rotateAngle);
	//m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
	update();
}

void xInterCoupleEntity::setShiftDistance(qreal dist)
{
	if (qFuzzyCompare(dist, m_shiftDist))
		return;

	prepareGeometryChange();
	m_shiftDist = dist;
	update();
}

void xInterCoupleEntity::bindEntity1(xEntity *e)
{
	if (e == m_bindEntity1)
		return;

	if (m_bindEntity1)
	{
		m_bindEntity1->disconnect(this);
	}

	if (e)
	{
		connect(e, &xEntity::shapeChanged, this, &xInterCoupleEntity::onEntity1Changed);
		connect(e, &xEntity::posChanged, this, &xInterCoupleEntity::onEntity1Moved);
		connect(e, &xEntity::destroyed, this, &xEntity::deleteLater);
	}

	m_bindEntity1 = e;
}

void xInterCoupleEntity::bindEntity2(xEntity *e)
{
	if (e == m_bindEntity2)
		return;

	if (m_bindEntity2)
	{
		m_bindEntity2->disconnect(this);
	}

	if (e)
	{
		connect(e, &xEntity::shapeChanged, this, &xInterCoupleEntity::onEntity2Changed);
		connect(e, &xEntity::posChanged, this, &xInterCoupleEntity::onEntity2Moved);
		connect(e, &xEntity::destroyed, this, &xEntity::deleteLater);
	}

	m_bindEntity2 = e;
}

void xInterCoupleEntity::moveBy(const QPointF &delta)
{
}

QList<QPointF> xInterCoupleEntity::controlPoints() const noexcept
{
	return QList<QPointF>();
}

void xInterCoupleEntity::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
}

bool xInterCoupleEntity::isCtrlPoint(const QPointF &p) const
{
	return false;
}

void xInterCoupleEntity::onEntity1Moved(const QPointF &delta)
{
}

void xInterCoupleEntity::onEntity2Moved(const QPointF &delta)
{
}
