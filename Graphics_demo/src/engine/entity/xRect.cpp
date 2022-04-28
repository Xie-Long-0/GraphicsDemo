#include "xRect.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xRect::xRect(xGraphicView* view, QGraphicsItem* parent)
	: xRegionEntity(view, parent)
{
}

xRect::xRect(const QRectF& rect, xGraphicView* view, QGraphicsItem* parent)
	: xRegionEntity(view, parent)
	, m_rect(rect)
{
}

xRect::xRect(const QPointF& topleft, const QPointF& botright, xGraphicView* view, QGraphicsItem* parent)
	: xRegionEntity(view, parent)
	, m_rect(topleft, botright)
{
}

xRect::~xRect()
{
}

int xRect::type() const
{
	return Type;
}

void xRect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	auto style = m_style;

	if (style != xStyle::NoStyle)
	{
		// ��ͣ״̬
		if (option->state & QStyle::State_MouseOver)
		{
			style = xStyle::RegHovered;
		}

		const qreal f = viewScaleFactor();
		xStyle::makeStyle(style, &m_pen, &m_brush, f);
	}

	painter->setPen(m_pen);
	painter->drawRect(m_rect);
	painter->fillRect(m_rect, m_brush);
}

QRectF xRect::boundingRect() const
{
	if (m_rect.isEmpty())
		return QRectF();
	qreal w = m_pen.widthF() * 2;
	return m_rect.marginsAdded({ w,w,w,w });
}

QPainterPath xRect::shape() const
{
	QPainterPath path;
	if (m_rect.isEmpty())
		return path;

	path.addRect(m_rect);
	path = StrokeShapeFromPath(path, m_pen.widthF() * 2);
	path.addRect(m_rect);
	return path;
}

void xRect::setRect(const QRectF& rect)
{
	if (rect == m_rect)
		return;

	prepareGeometryChange();
	m_rect = rect;
	update();
	emit shapeChanged();
}

void xRect::moveBy(const QPointF& delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_rect.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xRect::controlPoints() const
{
	return {m_rect.topLeft(), m_rect.topRight(), m_rect.bottomLeft(), m_rect.bottomRight()};
}

void xRect::moveCtrlPoint(const QPointF& pt, const QPointF& movedPt)
{
	prepareGeometryChange();

	if (Distance(m_rect.topLeft(), pt) < DELTA_DIST_2 / viewScaleFactor()) // �����½Ǻ����½��غ�ʱ��û�о�����
	{
		if (movedPt.x() > m_rect.topRight().x())
		{
			m_rect.setTopRight(movedPt);
		}
		else if (movedPt.y() > m_rect.bottomLeft().y())
		{
			m_rect.setBottomLeft(movedPt);
		}
		else
		{
			m_rect.setTopLeft(movedPt);

		}
		
	}
	else if (Distance(m_rect.topRight(), pt) < DELTA_DIST_2 / viewScaleFactor())
	{
		m_rect.setTopRight(movedPt);
	}
	else if (Distance(m_rect.bottomLeft(), pt) < DELTA_DIST_2 / viewScaleFactor())
	{
		m_rect.setBottomLeft(movedPt);
	}
	else if (Distance(m_rect.bottomRight(), pt) < DELTA_DIST_2 / viewScaleFactor())
	{
		m_rect.setBottomRight(movedPt);
	}
	update();
	emit shapeChanged();
	qDebug() << movedPt << m_rect;
}

bool xRect::isCtrlPoint(const QPointF& p) const
{
	if (Distance(m_rect.topLeft(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(m_rect.topRight(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(m_rect.bottomLeft(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(m_rect.bottomRight(), p) < DELTA_DIST_2 / viewScaleFactor())
		return true;
	return false;
}

bool xRect::isFittingEntity(const QPointF& p) const
{
	return false;
}

bool xRect::isRegionEdge(const QPointF& p) const
{
	return false;
}

void xRect::changeEdgeByPoint(const QPointF& p)
{
}
