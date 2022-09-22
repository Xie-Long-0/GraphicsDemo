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

	if (style != xDef::S_NoStyle)
	{
		if (isSelected())
		{
			style = xDef::S_Selected;
			// 若有父图元如xRegCircle，则同时将父图元设置为选中
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

	painter->setPen(m_pen);
	painter->drawEllipse(m_circle.boundingRect());

	if (isSelected() && (flags() & ItemIsMovable))
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
	if (!m_circle.isValid())
		return QRectF();

	// 计算图形在视场中的矩形，包括画笔的宽度，否则无法正确显示
	// Note：画笔宽度设置为2倍以便更容易被选中
	const qreal pw = m_pen.widthF() * 2;
	return m_circle.boundingRect().marginsAdded({ pw,pw,pw,pw });
}

QPainterPath xCircle::shape() const
{
	QPainterPath path;
	if (!m_circle.isValid())
		return path;

	path.addEllipse(m_circle.boundingRect());
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
	if (c == m_circle)
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

QList<QPointF> xCircle::controlPoints() const noexcept
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
