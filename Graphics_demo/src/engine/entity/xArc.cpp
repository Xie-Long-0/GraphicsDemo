#include "xArc.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

xArc::xArc(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xArc::xArc(const xArcData &arc, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_arc(arc)
{
}

xArc::xArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_arc(center, radius, angle, spanAngle)
{
}

xArc::xArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_arc(p1, p2, p3)
{
}

int xArc::type() const
{
	return Type;
}

void xArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	
}

QRectF xArc::boundingRect() const
{
	
	return QRectF();
}

QPainterPath xArc::shape() const
{
	return QPainterPath();
}

void xArc::setArc(const xArcData &arc)
{
}

void xArc::setArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
{
}

void xArc::setArc(const QPointF &p1, const QPointF &p2, const QPointF &p3)
{
}

void xArc::setRadius(qreal radius)
{
}

void xArc::setPt1(const QPointF &p)
{
}

void xArc::setPt2(const QPointF &p)
{
}

void xArc::setPt3(const QPointF &p)
{
}

void xArc::moveBy(const QPointF &delta)
{
}

QList<QPointF> xArc::controlPoints() const noexcept
{
	return QList<QPointF>();
}

void xArc::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
}

bool xArc::isCtrlPoint(const QPointF &p) const
{
	return false;
}
