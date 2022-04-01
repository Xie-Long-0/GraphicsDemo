#include "xRegLine.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

xRegLine::xRegLine(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
	m_subLine = new xLine(view, this);
	m_subLine->setFlag(ItemIsMovable, false);
	m_subLine->setFlag(ItemStacksBehindParent);
	m_subLine->hide();
}

xRegLine::xRegLine(const QLineF &line, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_regLine(line)
{
	m_subLine = new xLine(view);
	m_subLine->setFlag(ItemIsMovable, false);
	m_subLine->setFlag(ItemStacksBehindParent);
	m_subLine->hide();
}

xRegLine::xRegLine(const QPointF &p1, const QPointF &p2, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_regLine(p1, p2)
{
	m_subLine = new xLine(view);
	m_subLine->setFlag(ItemIsMovable, false);
	m_subLine->setFlag(ItemStacksBehindParent);
	m_subLine->hide();
}

xRegLine::~xRegLine()
{
}

int xRegLine::type() const
{
	return Type;
}

void xRegLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	const qreal angle = m_regLine.angle() * M_PI / 180.0;
	// ����4�����㣬line.p1����ߵĵ㿪ʼ��˳ʱ��
	const auto p1 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p1();
	const auto p2 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p2();
	const auto p3 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p2();
	const auto p4 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p1();

	// �߿�·��
	QPainterPath path;
	path.moveTo(p1);
	path.lineTo(p2);
	path.lineTo(p3);
	path.lineTo(p4);
	path.closeSubpath();

	auto style = m_style;
	const qreal f = viewScaleFactor();

	if (style != xStyle::NoStyle)
	{
		// ѡ��״̬
		if (option->state & QStyle::State_Selected)
		{
			style = xStyle::RegSelected;
			// ѡ��ʱ�滭�߿�
			painter->setPen(QPen(QColor(255, 255, 0, 255), 1.0 / f));
			painter->drawPath(path);
		}

		// ��ͣ״̬
		if (option->state & QStyle::State_MouseOver)
		{
			style = xStyle::RegHovered;
		}

		xStyle::makeStyle(style, &m_pen, &m_brush, f);
	}

	// ��䷶Χ
	painter->fillPath(path, m_brush);
	// ��������
	painter->setPen(m_pen);
	painter->drawLine(m_regLine);
	
	// ��������߼�ͷ
	const auto lp = PointFromPolar(14.0 / f, angle + M_PI - ANGLE_15_RAD) + m_regLine.p2();
	const auto rp = PointFromPolar(14.0 / f, angle + M_PI + ANGLE_15_RAD) + m_regLine.p2();
	QPainterPath ap;
	ap.moveTo(m_regLine.p2());
	ap.lineTo(lp);
	ap.lineTo(rp);
	ap.closeSubpath();
	painter->fillPath(ap, m_pen.color());

	// ѡ��ʱ�滭���Ƶ�
	if (option->state & QStyle::State_Selected)
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_regLine.x1() - w, m_regLine.y1() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_regLine.x2() - w, m_regLine.y2() - w, w + w, w + w), Qt::yellow);
	}
}

QRectF xRegLine::boundingRect() const
{
	if (m_regLine.isNull())
		return QRectF();

	const qreal angle = m_regLine.angle() * M_PI / 180.0;
	// ����4�����㣬line.p1����ߵĵ㿪ʼ��˳ʱ��
	const auto p1 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p1();
	const auto p2 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p2();
	const auto p3 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p2();
	const auto p4 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p1();

	const qreal sx = std::min({ p1.x(), p2.x(), p3.x(), p4.x() });
	const qreal bx = std::max({ p1.x(), p2.x(), p3.x(), p4.x() });
	const qreal sy = std::min({ p1.y(), p2.y(), p3.y(), p4.y() });
	const qreal by = std::max({ p1.y(), p2.y(), p3.y(), p4.y() });
	
	const qreal w = m_pen.widthF() * 2;
	return QRectF(sx - w, sy - w, bx - sx + w + w, by - sy + w + w);
}

QPainterPath xRegLine::shape() const
{
	QPainterPath path;
	if (m_regLine.isNull())
		return path;

	const qreal angle = m_regLine.angle() * M_PI / 180.0;
	// ����4�����㣬line.p1����ߵĵ㿪ʼ��˳ʱ��
	const auto p1 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p1();
	const auto p2 = PointFromPolar(m_width, angle + M_PI * 0.5) + m_regLine.p2();
	const auto p3 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p2();
	const auto p4 = PointFromPolar(m_width, angle - M_PI * 0.5) + m_regLine.p1();

	path.moveTo(p1);
	path.lineTo(p2);
	path.lineTo(p3);
	path.lineTo(p4);
	path.closeSubpath();

	if (m_pen.widthF() < 0.001)
		return path;

	auto ps = StrokeShapeFromPath(path, m_pen);
	ps.addPath(path);
	return ps;
}

void xRegLine::setSubLine(const QLineF &line)
{
	m_subLine->setLine(line.p1(), line.p2());
	m_subLine->setStyle(xStyle::Measured);
	m_subLine->show();
}

void xRegLine::setSubLine(const QPointF &p1, const QPointF &p2)
{
	m_subLine->setLine(p1, p2);
	m_subLine->setStyle(xStyle::Measured);
	m_subLine->show();
}

void xRegLine::hideSubLine(bool hide)
{
	m_subLine->setVisible(hide);
}

void xRegLine::setLine(const QPointF &p1, const QPointF &p2)
{
	auto sp1 = mapFromScene(p1);
	auto sp2 = mapFromScene(p2);
	if (m_regLine.p1() == sp1 && m_regLine.p2() == sp2)
		return;

	prepareGeometryChange();
	m_regLine.setPoints(sp1, sp2);
	update();
}

void xRegLine::setPt1(const QPointF &p)
{
	auto sp = mapFromScene(p);
	if (m_regLine.p1() == sp)
		return;

	prepareGeometryChange();
	m_regLine.setP1(sp);
	update();
}

void xRegLine::setPt2(const QPointF &p)
{
	auto sp = mapFromScene(p);
	if (m_regLine.p2() == sp)
		return;

	prepareGeometryChange();
	m_regLine.setP2(sp);
	update();
}

void xRegLine::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_regLine.translate(delta);
	update();
}

QList<QPointF> xRegLine::controlPoints() const
{
	return { pt1(),pt2() };
}

void xRegLine::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
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

bool xRegLine::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;
	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor());
}

void xRegLine::changeEdgeByPoint(const QPointF &p)
{
	auto sp = mapFromScene(p);
	setRegWidth(DistancePoint2Line(sp, m_regLine));
}

bool xRegLine::isRegionEdge(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	auto sp = mapFromScene(p);
	if (fabs(DistancePoint2Line(sp, m_regLine) - m_width) < DELTA_DIST_2 / viewScaleFactor())
		return true;
	return false;
}