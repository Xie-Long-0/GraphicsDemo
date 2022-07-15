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
	path.arcMoveTo(m_arc.boundingRect().marginsAdded({ w,w,w,w }), m_arc.angleDegree());
	path.arcTo(m_arc.boundingRect().marginsAdded({ w,w,w,w }), m_arc.angleDegree(), m_arc.spanAngleDegree());
	// �뾶���ڷ�Χ����ʱ������Բ��
	if (m_arc.radius() > w)
	{
		// ������һ��Բ����ʹ���䰴˳������
		path.arcTo(m_arc.boundingRect().marginsRemoved({ w,w,w,w }),
			m_arc.angleDegree() + m_arc.spanAngleDegree(), -m_arc.spanAngleDegree());
		path.closeSubpath();
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
		// ѡ��״̬
		if (isSelected())
		{
			m_subArc->setSelected(true);
			style = xDef::S_RegSelected;
			// ѡ��ʱ�滭�߿�
			painter->setPen(QPen(QColor(255, 255, 0, 255), 1.0 / f));
			painter->drawPath(path);
		}

		// ��ͣ״̬
		if (option->state & QStyle::State_MouseOver)
		{
			style = xDef::S_RegHovered;
		}

		MakeStyle(style, &m_pen, &m_brush, f);
	}

	// ��䷶Χ
	painter->fillPath(path, m_brush);
	// ������Բ��
	QPainterPath cpath;
	cpath.arcMoveTo(m_arc.boundingRect(), m_arc.angleDegree());
	cpath.arcTo(m_arc.boundingRect(), m_arc.angleDegree(), m_arc.spanAngleDegree());
	painter->setPen(m_pen);
	painter->drawPath(cpath);

	// ѡ��ʱ�滭���Ƶ�
	if (isSelected() && (flags() & ItemIsMovable))
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_arc.center().x() - w, m_arc.center().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt1().x() - w, m_arc.pt1().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt2().x() - w, m_arc.pt2().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_arc.pt3().x() - w, m_arc.pt3().y() - w, w + w, w + w), Qt::yellow);
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

	path.arcMoveTo(m_arc.boundingRect().marginsAdded({ pw,pw,pw,pw }), m_arc.angleDegree());
	path.arcTo(m_arc.boundingRect().marginsAdded({ pw,pw,pw,pw }), m_arc.angleDegree(), m_arc.spanAngleDegree());
	// �뾶���ڷ�Χ����ʱ������Բ��
	if (m_arc.radius() > m_width)
	{
		// ������һ��Բ����ʹ���䰴˳������
		path.arcTo(m_arc.boundingRect().marginsRemoved({ pw,pw,pw,pw }),
			m_arc.angleDegree() + m_arc.spanAngleDegree(), -m_arc.spanAngleDegree());
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
	// �ж��Ƿ���Բ���нǷ�Χ��
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