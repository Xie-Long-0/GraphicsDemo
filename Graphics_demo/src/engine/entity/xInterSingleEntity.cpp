#include "xInterSingleEntity.h"
#include <QFontMetrics>

xInterSingleEntity::xInterSingleEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xInterSingleEntity::~xInterSingleEntity()
{
}

void xInterSingleEntity::setText(const QString &text)
{
	if (text == m_text)
		return;

	prepareGeometryChange();
	m_text = text;
	m_lastFactor = -1;	// 文本改变时重新计算文本大小
	update();
}

void xInterSingleEntity::setBindPoint(const QPointF &p)
{
	if (p == m_bindPoint)
		return;

	prepareGeometryChange();
	m_bindPoint = p;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
	update();
}

void xInterSingleEntity::setAnchorPoint(const QPointF &p)
{
	if (p == m_anchorPoint)
		return;

	prepareGeometryChange();
	m_anchorPoint = p;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
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
	if (e == m_bindEntity)
		return;

	if (m_bindEntity)
	{
		m_bindEntity->disconnect(this);
		if (auto pe = m_bindEntity->parentEntity(); pe != nullptr)
		{
			pe->disconnect(this);
			pe->setNeedCalcFlag(false);
		}
		else
		{
			m_bindEntity->setNeedCalcFlag(false);
		}
	}

	if (e)
	{
		connect(e, &xEntity::shapeChanged, this, &xInterSingleEntity::onEntityChanged);
		connect(e, &xEntity::posChanged, this, &xInterSingleEntity::onEntityMoved);
		connect(e, &xEntity::destroyed, this, &xEntity::deleteLater);
		if (auto pe = e->parentEntity(); pe != nullptr)
		{
			connect(pe, &xEntity::requestCalc, this, &xInterSingleEntity::calculate);
			pe->setNeedCalcFlag(true);
		}
		else
		{
			connect(e, &xEntity::requestCalc, this, &xInterSingleEntity::calculate);
			e->setNeedCalcFlag(true);
		}
	}

	m_bindEntity = e;
}

void xInterSingleEntity::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_anchorPoint += delta;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
	update();
}

QList<QPointF> xInterSingleEntity::controlPoints() const noexcept
{
	return { m_anchorPoint };
}

void xInterSingleEntity::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
	if (Distance(pt, m_anchorPoint) < DELTA_DIST / viewScaleFactor())
	{
		setAnchorPoint(movedPt);
	}
}

bool xInterSingleEntity::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	return (Distance(m_anchorPoint, p) < DELTA_DIST_2 / viewScaleFactor());
}

void xInterSingleEntity::onEntityMoved(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_bindPoint += delta;
	m_rotateAngle = M_PI_2 - AnglePoint2Point(m_bindPoint, m_anchorPoint);
	m_transform.reset();
	m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	m_transform.rotateRadians(m_rotateAngle);
	m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
	update();
}
