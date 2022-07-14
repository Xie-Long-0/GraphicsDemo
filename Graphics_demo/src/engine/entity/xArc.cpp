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
	Q_UNUSED(widget);

	auto style = m_style;

	if (style != xDef::S_NoStyle)
	{
		if (isSelected())
		{
			style = xDef::S_Selected;
			// 若有父图元如xRegArc，则同时将父图元设置为选中
			if (auto parent = parentEntity(); parent != nullptr)
			{
				parent->setSelected(true);
				parent->setOpacity(1.0);
			}
		}
		else
		{
			// 若有父图元且父图元未选中，则隐藏父图元
			if (auto parent = parentEntity(); parent != nullptr && !parent->isSelected())
			{
				parent->setSelected(false);
				parent->setOpacity(0);
			}
		}

		if (option->state & QStyle::State_MouseOver)
		{
			if (style == xDef::S_Selected)
				style = xDef::S_HoverSelected;
			else
				style = xDef::S_Hovered;
		}

		const qreal f = viewScaleFactor();
		MakeStyle(style, &m_pen, nullptr, f);
	}

	QPainterPath path;
	path.arcMoveTo(m_arc.boundingRect(), m_arc.angleDegree());
	path.arcTo(m_arc.boundingRect(), m_arc.angleDegree(), m_arc.spanAngleDegree());
	painter->setPen(m_pen);
	painter->drawPath(path);

	if (isSelected() && (flags() & ItemIsMovable))
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_arc.center().x() - w, m_arc.center().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt1().x() - w, m_arc.pt1().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt2().x() - w, m_arc.pt2().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt3().x() - w, m_arc.pt3().y() - w, w + w, w + w), Qt::yellow);
	}
}

QRectF xArc::boundingRect() const
{
	if (!m_arc.isValid())
		return QRectF();

	const qreal m = m_pen.widthF() * 2;
	return m_arc.boundingRect().marginsAdded({ m,m,m,m });
}

QPainterPath xArc::shape() const
{
	QPainterPath path;
	if (!m_arc.isValid())
		return path;

	path.arcMoveTo(m_arc.boundingRect(), m_arc.angleDegree());
	path.arcTo(m_arc.boundingRect(), m_arc.angleDegree(), m_arc.spanAngleDegree());
	return StrokeShapeFromPath(path, m_pen.widthF() * 3);
}

void xArc::setArc(const xArcData &arc)
{
	if (arc == m_arc)
		return;

	prepareGeometryChange();
	m_arc = arc;
	update();
	emit shapeChanged();
}

void xArc::setArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
{
	auto arc = xArcData(center, radius, angle, spanAngle);
	if (arc == m_arc)
		return;

	prepareGeometryChange();
	m_arc = arc;
	update();
	emit shapeChanged();
}

void xArc::setArc(const QPointF &p1, const QPointF &p2, const QPointF &p3)
{
	auto arc = xArcData(p1, p2, p3);
	if (arc == m_arc)
		return;

	prepareGeometryChange();
	m_arc = arc;
	update();
	emit shapeChanged();
}

void xArc::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, m_arc.radius()))
		return;

	prepareGeometryChange();
	m_arc.setRadius(radius);
	update();
	emit shapeChanged();
}

void xArc::setPt1(const QPointF &p)
{
	if (p == m_arc.pt1())
		return;

	prepareGeometryChange();
	m_arc = xArcData(p, m_arc.pt2(), m_arc.pt3());
	update();
	emit shapeChanged();
}

void xArc::setPt2(const QPointF &p)
{
	if (p == m_arc.pt2())
		return;

	prepareGeometryChange();
	m_arc = xArcData(m_arc.pt1(), p, m_arc.pt3());
	update();
	emit shapeChanged();
}

void xArc::setPt3(const QPointF &p)
{
	if (p == m_arc.pt3())
		return;

	prepareGeometryChange();
	m_arc = xArcData(m_arc.pt1(), m_arc.pt2(), p);
	update();
	emit shapeChanged();
}

void xArc::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_arc.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xArc::controlPoints() const noexcept
{
	return { pt1(), pt2(), pt3() };
}

void xArc::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
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

bool xArc::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt3(), p) < DELTA_DIST_2 / viewScaleFactor());
}
