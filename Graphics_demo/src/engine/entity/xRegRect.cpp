#include "xRegRect.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xRegRect::xRegRect(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
}

xRegRect::xRegRect(const QRectF &rect, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
	// 令矩形的宽与高大于0
	auto nrect = rect.normalized();
	if (nrect.width() < 0.001)
		nrect.setWidth(0.001);
	if (nrect.height() < 0.001)
		nrect.setHeight(0.001);

	m_rect = nrect;
}

xRegRect::xRegRect(const QPointF &topleft, const QPointF &botright, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
	// 令矩形的宽与高大于0
	auto nrect = QRectF(topleft, botright).normalized();
	if (nrect.width() < 0.001)
		nrect.setWidth(0.001);
	if (nrect.height() < 0.001)
		nrect.setHeight(0.001);

	m_rect = nrect;
}

xRegRect::~xRegRect()
{
}

int xRegRect::type() const noexcept
{
	return Type;
}

void xRegRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (painter == nullptr)
    {
        qWarning() << __FUNCTION__ << "painter is a nullptr!";
        return;
    }

    auto style = m_style;

	if (style != xDef::S_NoStyle)
	{
		// 悬停状态
		if (option->state & QStyle::State_MouseOver)
		{
			style = xDef::S_RegHovered;
		}

		const qreal f = viewScaleFactor();
		MakeStyle(style, &m_pen, &m_brush, f);
	}

	painter->setPen(m_pen);
	painter->drawRect(m_rect);
	painter->fillRect(m_rect, m_brush);
}

QRectF xRegRect::boundingRect() const
{
	if (m_rect.isEmpty())
		return QRectF();
	const qreal w = m_pen.widthF() * 2;
	return m_rect.marginsAdded({ w,w,w,w });
}

QPainterPath xRegRect::shape() const
{
	QPainterPath path;
	if (m_rect.isEmpty())
		return path;

	path.addRect(m_rect);
	path = StrokeShapeFromPath(path, m_pen.widthF() * 2);
	path.addRect(m_rect);
	return path;
}

void xRegRect::setRect(const QRectF &rect)
{
	// 令矩形的宽与高大于0
	auto nrect = rect.normalized();
	if (nrect.width() < 0.001)
		nrect.setWidth(0.001);
	if (nrect.height() < 0.001)
		nrect.setHeight(0.001);

	if (nrect == m_rect)
		return;

	prepareGeometryChange();
	m_rect = nrect;
	update();
	emit shapeChanged();
}

void xRegRect::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_rect.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xRegRect::controlPoints() const
{
	return { m_rect.topLeft(), m_rect.topRight(), m_rect.bottomLeft(), m_rect.bottomRight() };
}

void xRegRect::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
{
	const auto tl = Distance(m_rect.topLeft(), pt);
	const auto tr = Distance(m_rect.topRight(), pt);
	const auto bl = Distance(m_rect.bottomLeft(), pt);
	const auto br = Distance(m_rect.bottomRight(), pt);

	const auto min = std::min({ tl,tr,bl,br });

	// 移动左上角
	if (qFuzzyCompare(min, tl) && tl < DELTA_DIST / viewScaleFactor())
	{
		// 从左上角移到右下角时需要把movedPt当成右下角的点
		if (movedPt.x() - m_rect.right() > 0.001 &&
			movedPt.y() - m_rect.bottom() > 0.001)
		{
			setRect(m_rect.topLeft(), movedPt);
		}
		// 从左上角移到右上角时需要把movedPt当成右上角的点
		else if (movedPt.x() - m_rect.right() > 0.001)
		{
			setRect(m_rect.bottomLeft(), movedPt);
		}
		// 从左上角移到左下角时需要把movedPt当成左下角的点
		else if (movedPt.y() - m_rect.bottom() > 0.001)
		{
			setRect(m_rect.topRight(), movedPt);
		}
		else
		{
			setRect(movedPt, m_rect.bottomRight());
		}
	}
	// 移动右上角
	else if (qFuzzyCompare(min, tr) && tr < DELTA_DIST / viewScaleFactor())
	{
		// 从右上角移到右下角时需要把movedPt当成右下角的点
		if (movedPt.y() - m_rect.bottom() > 0.001)
		{
			setRect(m_rect.topLeft(), movedPt);
		}
		else
		{
			setRect(movedPt, m_rect.bottomLeft());
		}
	}
	// 移动左下角
	else if (qFuzzyCompare(min, bl) && bl < DELTA_DIST / viewScaleFactor())
	{
		// 从左下角移到右下角时需要把movedPt当成右下角的点
		if (movedPt.x() - m_rect.right() > 0.001)
		{
			setRect(m_rect.topLeft(), movedPt);
		}
		else
		{
			setRect(movedPt, m_rect.topRight());
		}
	}
	// 移动右下角
	else if (qFuzzyCompare(min, br) && br < DELTA_DIST / viewScaleFactor())
	{
		setRect(m_rect.topLeft(), movedPt);
	}
}

bool xRegRect::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	if (Distance(m_rect.topLeft(), p) < DELTA_DIST / viewScaleFactor()
		|| Distance(m_rect.topRight(), p) < DELTA_DIST / viewScaleFactor()
		|| Distance(m_rect.bottomLeft(), p) < DELTA_DIST / viewScaleFactor()
		|| Distance(m_rect.bottomRight(), p) < DELTA_DIST / viewScaleFactor())
		return true;
	return false;
}

bool xRegRect::isRegionEdge(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	const auto dl = fabs(p.x() - m_rect.left());
	const auto dt = fabs(p.y() - m_rect.top());
	const auto dr = fabs(p.x() - m_rect.right());
	const auto db = fabs(p.y() - m_rect.bottom());

	const auto min = std::min({ dl,dt,dr,db });

	if (min < DELTA_DIST / viewScaleFactor())
		return true;

	return false;
}

void xRegRect::changeEdgeByPoint(const QPointF &p)
{
	const auto dl = fabs(p.x() - m_rect.left());
	const auto dt = fabs(p.y() - m_rect.top());
	const auto dr = fabs(p.x() - m_rect.right());
	const auto db = fabs(p.y() - m_rect.bottom());

	const auto min = std::min({ dl,dt,dr,db });

	prepareGeometryChange();
	if (qFuzzyCompare(min, dl))
	{
		m_rect.setLeft(p.x());
	}
	else if (qFuzzyCompare(min, dt))
	{
		m_rect.setTop(p.y());
	}
	else if (qFuzzyCompare(min, dr))
	{
		m_rect.setRight(p.x());
	}
	else
	{
		m_rect.setBottom(p.y());
	}
	update();
	emit shapeChanged();
}
