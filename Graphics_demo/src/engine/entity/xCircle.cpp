#include "xCircle.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xCircle::xCircle(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	init();
}

xCircle::xCircle(const xCircleData &circle, QGraphicsItem *parent)
	: QGraphicsItem(parent)
	, m_circle(circle)
{
	init();
}

xCircle::xCircle(const QPointF &center, qreal radius, QGraphicsItem *parent)
	: QGraphicsItem(parent)
	, m_circle(center, radius)
{
	init();
}

xCircle::xCircle(qreal cx, qreal cy, qreal radius, QGraphicsItem *parent)
	: QGraphicsItem(parent)
	, m_circle(cx, cy, radius)
{
	init();
}

xCircle::xCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QGraphicsItem *parent)
	: QGraphicsItem(parent)
	, m_circle(p1, p2, p3)
{
	init();
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

		qreal f = viewScaleFactor();
		xStyle::makeStyle(style, &m_pen, nullptr, f);
	}

	painter->setPen(m_pen);
	painter->drawEllipse(m_circle.center(), m_circle.radius(), m_circle.radius());

	if (option->state & QStyle::State_Selected)
	{
		qreal w = m_pen.widthF();
		painter->fillRect(m_circle.center().x() - w, m_circle.center().y() - w, w + w, w + w, Qt::yellow);
		painter->fillRect(m_circle.pt1().x() - w, m_circle.pt1().y() - w, w + w, w + w, Qt::yellow);
		painter->fillRect(m_circle.pt2().x() - w, m_circle.pt2().y() - w, w + w, w + w, Qt::yellow);
		painter->fillRect(m_circle.pt3().x() - w, m_circle.pt3().y() - w, w + w, w + w, Qt::yellow);
	}
}

QRectF xCircle::boundingRect() const
{
	// 计算图形在视场中的矩形，包括画笔的宽度，否则无法正确显示
	qreal pw = m_pen.widthF() * 2;
	qreal x = m_circle.center().x() - m_circle.radius() - pw;
	qreal y = m_circle.center().y() - m_circle.radius() - pw;
	qreal w = m_circle.radius() + pw;
	return QRectF(x, y, w + w, w + w);
}

QPainterPath xCircle::shape() const
{
	QPainterPath path;
	if (m_circle.isNull())
		return path;

	path.addEllipse(m_circle.center(), m_circle.radius(), m_circle.radius());
	return StrokeShapeFromPath(path, m_pen);
}

xCircleData xCircle::circleData() const
{
	return xCircleData(center(), radius());
}

void xCircle::setCircle(const xCircleData &circle)
{
	if (circle == m_circle)
		return;

	prepareGeometryChange();
	m_circle = circle;
	update();
}

void xCircle::setCircle(const QPointF &center, qreal radius)
{
	if (center == m_circle.center() && radius == m_circle.radius())
		return;

	prepareGeometryChange();
	m_circle = xCircleData(center, radius);
	update();
}

QPointF xCircle::center() const
{
	return mapToScene(m_circle.center());
}

void xCircle::setCenter(const QPointF &center)
{
	if (center == m_circle.center())
		return;

	prepareGeometryChange();
	m_circle.setCenter(center);
	update();
}

void xCircle::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, m_circle.radius()))
		return;

	prepareGeometryChange();
	m_circle.setRadius(radius);
	update();
}

void xCircle::setPen(const QPen &pen)
{
	if (pen == m_pen)
		return;

	prepareGeometryChange();
	m_pen = pen;
	m_style = xStyle::NoStyle;	// 设置无样式以使用手动设置的笔画
	update();
}

void xCircle::setStyle(xStyle::Style style)
{
	if (style == m_style)
		return;

	prepareGeometryChange();
	m_style = style;
	update();
}

qreal xCircle::viewScaleFactor() const
{
	// 通过view的转换矩阵获取缩放系数
	return scene()->views()[0]->transform().m11();
}