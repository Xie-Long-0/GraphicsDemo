#include "xCircle.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xCircle::xCircle(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xCircle::xCircle(const xCircleData &circle, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_circle(circle)
{
}

xCircle::xCircle(const QPointF &center, qreal radius, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_circle(center, radius)
{
}

xCircle::xCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_circle(p1, p2, p3)
{
}

int xCircle::type() const
{
	return Type;
}

void xCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	auto style = m_style;

	if (style != xStyle::NoStyle)
	{
		if (option->state & QStyle::State_Selected)
		{
			style = xStyle::Selected;
		}

		if (option->state & QStyle::State_MouseOver)
		{
			if (style == xStyle::Selected)
				style = xStyle::HoverSelected;
			else
				style = xStyle::Hovered;
		}

		const qreal f = viewScaleFactor();
		xStyle::makeStyle(style, &m_pen, nullptr, f);
	}

	painter->setPen(m_pen);
	painter->drawEllipse(m_circle.center(), m_circle.radius(), m_circle.radius());

	if ((option->state & QStyle::State_Selected) && (flags() & ItemIsMovable))
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_circle.center().x() - w, m_circle.center().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_circle.pt1().x() - w, m_circle.pt1().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_circle.pt2().x() - w, m_circle.pt2().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_circle.pt3().x() - w, m_circle.pt3().y() - w, w + w, w + w), Qt::yellow);
	}
}

QRectF xCircle::boundingRect() const
{
	if (m_circle.isNull())
		return QRectF();

	// 计算图形在视场中的矩形，包括画笔的宽度，否则无法正确显示
	// Note：画笔宽度设置为2倍以便更容易被选中
	const qreal pw = m_pen.widthF() * 2;
	const qreal x = m_circle.center().x() - m_circle.radius() - pw;
	const qreal y = m_circle.center().y() - m_circle.radius() - pw;
	const qreal w = m_circle.radius() + pw;
	return QRectF(x, y, w + w, w + w);
}

QPainterPath xCircle::shape() const
{
	QPainterPath path;
	if (m_circle.isNull())
		return path;

	path.addEllipse(m_circle.center(), m_circle.radius(), m_circle.radius());
	return StrokeShapeFromPath(path, m_pen.widthF() * 2);
}

void xCircle::setCircle(const QPointF &center, qreal radius)
{
	if (center == m_circle.center() && qFuzzyCompare(radius, m_circle.radius()))
		return;

	prepareGeometryChange();
	m_circle = xCircleData(center, radius);
	update();
	emit shapeChanged();
}

void xCircle::setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3)
{
	auto c = xCircleData(p1, p2, p3);
	if (c.center() == m_circle.center() && qFuzzyCompare(c.radius(), m_circle.radius()))
		return;

	prepareGeometryChange();
	m_circle = c;
	update();
	emit shapeChanged();
}

void xCircle::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, m_circle.radius()))
		return;

	prepareGeometryChange();
	m_circle.setRadius(radius);
	update();
	emit shapeChanged();
}

void xCircle::setPt1(const QPointF &p)
{
	if (p == m_circle.pt1())
		return;

	prepareGeometryChange();
	m_circle = xCircleData(p, m_circle.pt2(), m_circle.pt3());
	update();
	emit shapeChanged();
}

void xCircle::setPt2(const QPointF &p)
{
	if (p == m_circle.pt2())
		return;

	prepareGeometryChange();
	m_circle = xCircleData(m_circle.pt1(), p, m_circle.pt3());
	update();
	emit shapeChanged();
}

void xCircle::setPt3(const QPointF &p)
{
	if (p == m_circle.pt3())
		return;

	prepareGeometryChange();
	m_circle = xCircleData(m_circle.pt1(), m_circle.pt2(), p);
	update();
	emit shapeChanged();
}

void xCircle::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_circle.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xCircle::controlPoints() const
{
	return { pt1(), pt2(), pt3() };
}

void xCircle::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
	if (Distance(pt, pt1()) < DELTA_DIST / viewScaleFactor())
	{
		setPt1(movedPt);
	}
	else if (Distance(pt, pt2()) < DELTA_DIST / viewScaleFactor())
	{
		setPt2(movedPt);
	}
	else if (Distance(pt, pt3()) < DELTA_DIST / viewScaleFactor())
	{
		setPt3(movedPt);
	}
}

bool xCircle::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt3(), p) < DELTA_DIST_2 / viewScaleFactor());
}
