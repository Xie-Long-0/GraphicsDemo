#include "xRegArc.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

xRegArc::xRegArc(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
	m_subArc = new xArc(view, this);
	m_subArc->setFlag(ItemIsMovable, false);
	m_subArc->setFlag(ItemStacksBehindParent);
	m_subArc->hide();
}

xRegArc::xRegArc(const xArcData &arc, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_arc(arc)
{
	m_subArc = new xArc(view, this);
	m_subArc->setFlag(ItemIsMovable, false);
	m_subArc->setFlag(ItemStacksBehindParent);
	m_subArc->hide();
}

xRegArc::xRegArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_arc(center, radius, angle, spanAngle)
{
	m_subArc = new xArc(view, this);
	m_subArc->setFlag(ItemIsMovable, false);
	m_subArc->setFlag(ItemStacksBehindParent);
	m_subArc->hide();
}

xRegArc::xRegArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_arc(p1, p2, p3)
{
	m_subArc = new xArc(view, this);
	m_subArc->setFlag(ItemIsMovable, false);
	m_subArc->setFlag(ItemStacksBehindParent);
	m_subArc->hide();
}

int xRegArc::type() const
{
	return Type;
}

void xRegArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	const qreal w = m_width;
	QPainterPath path;
	path.addPolygon(ArcToPolygon(center(), radius() + w, angle(), spanAngle()));
	// 半径大于范围宽度时加入内圆弧
	if (m_arc.radius() > w)
	{
		// 内外两个圆弧端点连接线
		path.lineTo(center() + PointFromPolar(radius() - w, angle() + spanAngle()));
		// 添加另一个反向圆弧，使用其按顺序连线
		path.addPolygon(ArcToPolygon(center(), radius() - w, angle() + spanAngle(), -spanAngle()));
		path.lineTo(center() + PointFromPolar(radius() + w, angle()));
	}
	else
	{
		path.lineTo(m_arc.center());
		path.closeSubpath();
	}

	auto style = m_style;
	const qreal f = viewScaleFactor();

	if (style != xDef::S_NoStyle)
	{
		// 选中状态
		if (isSelected())
		{
			m_subArc->setSelected(true);
			style = xDef::S_RegSelected;
			// 选中时绘画边框
			painter->setPen(QPen(QColor(255, 255, 0, 255), 1.0 / f));
			painter->drawPath(path);
		}

		// 悬停状态
		if (option->state & QStyle::State_MouseOver)
		{
			style = xDef::S_RegHovered;
		}

		MakeStyle(style, &m_pen, &m_brush, f);
	}

	// 填充范围
	painter->fillPath(path, m_brush);
	// 画中心圆弧
	painter->setPen(m_pen);
	painter->drawPolyline(ArcToPolygon(m_arc));

	// 选中时绘画控制点
	if (isSelected() && (flags() & ItemIsMovable))
	{
		const qreal w = m_pen.widthF();
		FillRectByPoint(painter, m_arc.center(), w, Qt::yellow);
		FillRectByPoint(painter, m_arc.pt1(), w, Qt::yellow);
		FillRectByPoint(painter, m_arc.pt2(), w, Qt::yellow);
		FillRectByPoint(painter, m_arc.pt3(), w, Qt::yellow);
	}
}

QRectF xRegArc::boundingRect() const
{
	if (!m_arc.isValid())
		return QRectF();

	const qreal pw = m_pen.widthF() * 2 + m_width;
	return m_arc.boundingRect().marginsAdded({ pw,pw,pw,pw });
}

QPainterPath xRegArc::shape() const
{
	QPainterPath path;
	if (!m_arc.isValid())
		return path;

	const qreal pw = m_pen.widthF() + m_width;

	path.addPolygon(ArcToPolygon(center(), radius() + pw, angle(), spanAngle()));
	// 半径大于范围宽度时加入内圆弧
	if (m_arc.radius() > m_width)
	{
		// 添加另一个反向圆弧，使用其按顺序连线
		path.addPolygon(ArcToPolygon(center(), radius() - pw, angle() + spanAngle(), -spanAngle()));
		path.closeSubpath();
	}
	else
	{
		path.lineTo(m_arc.center());
		path.closeSubpath();
	}
	return path;
}

void xRegArc::setSubArc(const xArcData &arc)
{
	m_subArc->setArc(arc);
	m_subArc->setStyle(xDef::S_Measured);
	m_subArc->show();
	hideThis();
}

void xRegArc::setSubArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
{
	m_subArc->setArc(center, radius, angle, spanAngle);
	m_subArc->setStyle(xDef::S_Measured);
	m_subArc->show();
	hideThis();
}

void xRegArc::setArc(const xArcData &arc, qreal width)
{
	if (arc == m_arc && qFuzzyCompare(width, m_width))
		return;

	prepareGeometryChange();
	m_arc = arc;
	m_width = width;
	update();
	emit shapeChanged();
}

void xRegArc::setArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, qreal width)
{
	auto arc = xArcData(center, radius, angle, spanAngle);
	if (arc == m_arc && qFuzzyCompare(width, m_width))
		return;

	prepareGeometryChange();
	m_arc = arc;
	m_width = width;
	update();
	emit shapeChanged();
}

void xRegArc::setArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width)
{
	auto arc = xArcData(p1, p2, p3);
	if (arc == m_arc && qFuzzyCompare(width, m_width))
		return;

	prepareGeometryChange();
	m_arc = arc;
	m_width = width;
	update();
	emit shapeChanged();
}

void xRegArc::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, m_arc.radius()))
		return;

	prepareGeometryChange();
	m_arc.setRadius(radius);
	update();
	emit shapeChanged();
}

void xRegArc::setAngle(qreal angle)
{
	if (qFuzzyCompare(angle, m_arc.angle()))
		return;

	prepareGeometryChange();
	m_arc.setAngle(angle);
	update();
	emit shapeChanged();
}

void xRegArc::setSpanAngle(qreal angle)
{
	if (qFuzzyCompare(angle, m_arc.spanAngle()))
		return;

	prepareGeometryChange();
	m_arc.setSpanAngle(angle);
	update();
	emit shapeChanged();
}

void xRegArc::setAngleDegree(qreal angle)
{
	if (qFuzzyCompare(angle, m_arc.angleDegree()))
		return;

	prepareGeometryChange();
	m_arc.setAngleDegree(angle);
	update();
	emit shapeChanged();
}

void xRegArc::setSpanAngleDegree(qreal angle)
{
	if (qFuzzyCompare(angle, m_arc.spanAngleDegree()))
		return;

	prepareGeometryChange();
	m_arc.setSpanAngleDegree(angle);
	update();
	emit shapeChanged();
}

void xRegArc::setPt1(const QPointF &p)
{
	if (p == m_arc.pt1())
		return;

	prepareGeometryChange();
	m_arc = xArcData(p, m_arc.pt2(), m_arc.pt3());
	update();
	emit shapeChanged();
}

void xRegArc::setPt2(const QPointF &p)
{
	if (p == m_arc.pt2())
		return;

	prepareGeometryChange();
	m_arc = xArcData(m_arc.pt1(), p, m_arc.pt3());
	update();
	emit shapeChanged();
}

void xRegArc::setPt3(const QPointF &p)
{
	if (p == m_arc.pt3())
		return;

	prepareGeometryChange();
	m_arc = xArcData(m_arc.pt1(), m_arc.pt2(), p);
	update();
	emit shapeChanged();
}

void xRegArc::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_arc.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xRegArc::controlPoints() const noexcept
{
	return { pt1(), pt2(), pt3() };
}

void xRegArc::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
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

bool xRegArc::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt3(), p) < DELTA_DIST_2 / viewScaleFactor());
}

void xRegArc::changeEdgeByPoint(const QPointF &p)
{
	const qreal a = AnglePoint2Point(m_arc.center(), p);
	// 判断是否在圆弧夹角范围内
	if (!AngleIsBetween(a, m_arc.angle(), m_arc.spanAngle()))
	{
		return;
	}
	const qreal dw = fabs(Distance(p, m_arc.center()) - m_arc.radius());
	setRegWidth(dw);
}

bool xRegArc::isRegionEdge(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	const qreal dw = fabs(Distance(p, m_arc.center()) - m_arc.radius());
	if (fabs(dw - m_width) < DELTA_DIST_2 / viewScaleFactor())
		return true;
	return false;
}
