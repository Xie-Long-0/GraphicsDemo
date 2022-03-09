#include "xLine.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xLine::xLine(QGraphicsItem *parent)
	: QGraphicsLineItem(parent)
{
	init();
}

xLine::xLine(const QLineF &line, QGraphicsItem *parent)
	: QGraphicsLineItem(line, parent)
{
	init();
}

xLine::xLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
	: QGraphicsLineItem(x1, y1, x2, y2, parent)
{
	init();
}

xLine::xLine(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent)
	: QGraphicsLineItem(QLineF(p1, p2), parent)
{
	init();
}

int xLine::type() const
{
	return Type;
}

void xLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	auto style = m_style;

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
	// 由于父类QGraphicsLineItem存在私有成员pen，需要设置自己的m_pen以使shape()、boundingRect()等函数正确计算
	setPen(m_pen);
	painter->setPen(m_pen);
	auto l = line();
	painter->drawLine(l);

	if (style == xStyle::Selected)
	{
		painter->fillRect(l.x1() - 2.0 / f, l.y1() - 2.0 / f, 4.0 / f, 4.0 / f, Qt::yellow);
		painter->fillRect(l.x2() - 2.0 / f, l.y2() - 2.0 / f, 4.0 / f, 4.0 / f, Qt::yellow);
	}
}

QLineF xLine::line() const
{
	return QLineF(pt1(), pt2());
}

void xLine::setPt1(const QPointF &p)
{
	if (pt1() == p)
		return;

	auto l = line();
	l.setP1(mapFromScene(p));
	setLine(l);
}

void xLine::setPt2(const QPointF &p)
{
	if (pt2() == p)
		return;

	auto l = line();
	l.setP2(mapFromScene(p));
	setLine(l);
}

QPointF xLine::pt1() const
{
	return mapToScene(line().p1());
}

QPointF xLine::pt2() const
{
	return mapToScene(line().p2());
}

qreal xLine::viewScaleFactor() const
{
	// 通过view的转换矩阵获取缩放系数
	return scene()->views()[0]->transform().m11();
}

inline void xLine::init()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}
