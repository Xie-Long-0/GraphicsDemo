#include "xLine.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xLine::xLine(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
}

xLine::xLine(const QLineF &line, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_line(line)
{
}

xLine::xLine(const QPointF &p1, const QPointF &p2, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_line(p1, p2)
{
}

int xLine::type() const
{
	return Type;
}

void xLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	auto style = m_style;

	if (style != xStyle::NoStyle)
	{
		// 选中状态
		if (option->state & QStyle::State_Selected)
		{
			style = xStyle::Selected;
		}

		// 悬停状态
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
	painter->drawLine(m_line);

	// 选中时绘画控制点
	if (option->state & QStyle::State_Selected)
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_line.x1() - w, m_line.y1() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_line.x2() - w, m_line.y2() - w, w + w, w + w), Qt::yellow);
	}
}

QRectF xLine::boundingRect() const
{
	if (m_line.isNull())
		return QRectF();

	// 计算图形在视场中的矩形，包括画笔的宽度，否则无法正确显示
	// Note：画笔宽度设置为2倍以便更容易被选中
	const qreal w = m_pen.widthF() * 2;
	const qreal sx = std::min(m_line.x1(), m_line.x2());
	const qreal bx = std::max(m_line.x1(), m_line.x2());
	const qreal sy = std::min(m_line.y1(), m_line.y2());
	const qreal by = std::max(m_line.y1(), m_line.y2());
	return QRectF(sx - w, sy - w, bx - sx + w + w, by - sy + w + w);
}

QPainterPath xLine::shape() const
{
	QPainterPath path;
	if (m_line.isNull())
		return path;

	path.moveTo(m_line.p1());
	path.lineTo(m_line.p2());
	return StrokeShapeFromPath(path, m_pen);
}

void xLine::setLine(const QPointF &p1, const QPointF &p2)
{
	auto sp1 = mapFromScene(p1);
	auto sp2 = mapFromScene(p2);
	if (m_line.p1() == sp1 && m_line.p2() == sp2)
		return;

	prepareGeometryChange();
	m_line.setPoints(sp1, sp2);
	update();
}

void xLine::setPt1(const QPointF &p)
{
	auto sp = mapFromScene(p);
	if (m_line.p1() == sp)
		return;

	prepareGeometryChange();
	m_line.setP1(sp);
	update();
}

void xLine::setPt2(const QPointF &p)
{
	auto sp = mapFromScene(p);
	if (m_line.p2() == sp)
		return;

	prepareGeometryChange();
	m_line.setP2(sp);
	update();
}

void xLine::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_line.translate(delta);
	update();
}

QList<QPointF> xLine::controlPoints() const
{
	return { pt1(), pt2() };
}

void xLine::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
	if (Distance(pt, pt1()) < DELTA_DIST / viewScaleFactor())
	{
		setPt1(movedPt);
	}
	else if (Distance(pt, pt2()) < DELTA_DIST / viewScaleFactor())
	{
		setPt2(movedPt);
	}
}

bool xLine::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;
	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor());
}
