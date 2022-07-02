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

	if (style != xDef::S_NoStyle)
	{
		// 选中状态
		if (isSelected())
		{
			style = xDef::S_Selected;
			// 若有父图元如xRegLine，则同时将父图元设置为选中
			if (auto parent = parentItem(); parent != nullptr)
			{
				parent->setSelected(true);
				parent->setOpacity(1.0);
			}
		}
		else
		{
			// 若有父图元且父图元未选中，则隐藏父图元
			if (auto parent = parentItem(); parent != nullptr && !parent->isSelected())
			{
				parent->setSelected(false);
				parent->setOpacity(0);
			}
		}

		// 悬停状态
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
	painter->drawLine(m_line);

	// 选中时绘画控制点
	if (isSelected() && (flags() & ItemIsMovable))
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
	return StrokeShapeFromPath(path, m_pen.widthF() * 2);
}

void xLine::setLine(const QPointF &p1, const QPointF &p2)
{
	if (m_line.p1() == p1 && m_line.p2() == p2)
		return;

	prepareGeometryChange();
	m_line.setPoints(p1, p2);
	update();
	emit shapeChanged();
}

void xLine::setPt1(const QPointF &p)
{
	if (m_line.p1() == p)
		return;

	prepareGeometryChange();
	m_line.setP1(p);
	update();
	emit shapeChanged();
}

void xLine::setPt2(const QPointF &p)
{
	if (m_line.p2() == p)
		return;

	prepareGeometryChange();
	m_line.setP2(p);
	update();
	emit shapeChanged();
}

void xLine::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_line.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xLine::controlPoints() const noexcept
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
