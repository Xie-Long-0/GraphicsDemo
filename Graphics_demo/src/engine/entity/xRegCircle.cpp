#include "xRegCircle.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

xRegCircle::xRegCircle(xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(view, parent)
{
	m_subCircle = new xCircle(view, this);
	m_subCircle->setFlag(ItemIsMovable, false);
	m_subCircle->setFlag(ItemStacksBehindParent);
	m_subCircle->hide();
}

xRegCircle::xRegCircle(const xCircleData &circle, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_regCircle(circle)
{
	m_subCircle = new xCircle(view, this);
	m_subCircle->setFlag(ItemIsMovable, false);
	m_subCircle->setFlag(ItemStacksBehindParent);
	m_subCircle->hide();
}

xRegCircle::xRegCircle(const QPointF &center, qreal radius, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_regCircle(center, radius)
{
	m_subCircle = new xCircle(view, this);
	m_subCircle->setFlag(ItemIsMovable, false);
	m_subCircle->setFlag(ItemStacksBehindParent);
	m_subCircle->hide();
}

xRegCircle::xRegCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xRegionEntity(width, view, parent)
	, m_regCircle(p1, p2, p3)
{
	m_subCircle = new xCircle(view, this);
	m_subCircle->setFlag(ItemIsMovable, false);
	m_subCircle->setFlag(ItemStacksBehindParent);
	m_subCircle->hide();
}

int xRegCircle::type() const noexcept
{
	return Type;
}

void xRegCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (painter == nullptr)
    {
        qWarning() << __FUNCTION__ << "painter is a nullptr!";
        return;
    }
    Q_UNUSED(widget);

	const qreal r = m_regCircle.radius();
	QPainterPath path;
	// 外圆轮廓
	path.addEllipse(m_regCircle.center(), r + m_width, r + m_width);
	if (r > m_width)
		// 内圆轮廓
		path.addEllipse(m_regCircle.center(), r - m_width, r - m_width);

	auto style = m_style;
	const qreal f = viewScaleFactor();

	if (style != xDef::S_NoStyle)
	{
		// 选中状态
		if (isSelected())
		{
			m_subCircle->setSelected(true);
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
	// 画中心圆
	painter->setPen(m_pen);
	painter->drawEllipse(m_regCircle.boundingRect());

	// 选中时绘画控制点
	if (isSelected() && (flags() & ItemIsMovable))
	{
		const qreal w = m_pen.widthF();
		painter->fillRect(QRectF(m_regCircle.center().x() - w, m_regCircle.center().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_regCircle.pt1().x() - w, m_regCircle.pt1().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_regCircle.pt2().x() - w, m_regCircle.pt2().y() - w, w + w, w + w), Qt::yellow);
		painter->fillRect(QRectF(m_regCircle.pt3().x() - w, m_regCircle.pt3().y() - w, w + w, w + w), Qt::yellow);
	}
}

QRectF xRegCircle::boundingRect() const
{
	if (!m_regCircle.isValid())
		return QRectF();

	// 计算图形在视场中的矩形，包括画笔的宽度，否则无法正确显示
	// Note：画笔宽度设置为2倍以便更容易被选中
	const qreal pw = m_pen.widthF() * 2;
	const qreal x = m_regCircle.center().x() - m_regCircle.radius() - m_width - pw;
	const qreal y = m_regCircle.center().y() - m_regCircle.radius() - m_width - pw;
	const qreal w = m_regCircle.radius() + m_width + pw;
	return QRectF(x, y, w + w, w + w);
}

QPainterPath xRegCircle::shape() const
{
	QPainterPath path;
	if (!m_regCircle.isValid())
		return path;

	const qreal r = m_regCircle.radius();
	const qreal pw = m_pen.widthF();
	path.addEllipse(m_regCircle.center(), r + m_width + pw, r + m_width + pw);
	if (r > m_width)
		path.addEllipse(m_regCircle.center(), r - m_width - pw, r - m_width - pw);
	return path;
}

void xRegCircle::setSubCircle(const xCircleData &circle)
{
	m_subCircle->setCircle(circle);
	m_subCircle->setStyle(xDef::S_Measured);
	m_subCircle->show();
	hideThis();
}

void xRegCircle::setSubCircle(const QPointF &center, qreal radius)
{
	m_subCircle->setCircle(center, radius);
	m_subCircle->setStyle(xDef::S_Measured);
	m_subCircle->show();
	hideThis();
}

void xRegCircle::setCircle(const QPointF &center, qreal radius, qreal width)
{
	if (center == m_regCircle.center() && qFuzzyCompare(radius, m_regCircle.radius()) && qFuzzyCompare(width, m_width))
		return;

	prepareGeometryChange();
	m_regCircle = xCircleData(center, radius);
	m_width = width;
	update();
	emit shapeChanged();
}

void xRegCircle::setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width)
{
	const auto c = xCircleData(p1, p2, p3);
	if (c.center() == m_regCircle.center() && qFuzzyCompare(c.radius(), m_regCircle.radius()) && qFuzzyCompare(width, m_width))
		return;

	prepareGeometryChange();
	m_regCircle = c;
	m_width = width;
	update();
	emit shapeChanged();
}

void xRegCircle::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, m_regCircle.radius()))
		return;

	prepareGeometryChange();
	m_regCircle.setRadius(radius);
	update();
	emit shapeChanged();
}

void xRegCircle::setPt1(const QPointF &p)
{
	if (p == m_regCircle.pt1())
		return;

	prepareGeometryChange();
	m_regCircle = xCircleData(p, m_regCircle.pt2(), m_regCircle.pt3());
	update();
	emit shapeChanged();
}

void xRegCircle::setPt2(const QPointF &p)
{
	if (p == m_regCircle.pt2())
		return;

	prepareGeometryChange();
	m_regCircle = xCircleData(m_regCircle.pt1(), p, m_regCircle.pt3());
	update();
	emit shapeChanged();
}

void xRegCircle::setPt3(const QPointF &p)
{
	if (p == m_regCircle.pt3())
		return;

	prepareGeometryChange();
	m_regCircle = xCircleData(m_regCircle.pt1(), m_regCircle.pt2(), p);
	update();
	emit shapeChanged();
}

void xRegCircle::moveBy(const QPointF &delta)
{
	if (delta.isNull())
		return;

	prepareGeometryChange();
	m_regCircle.translate(delta);
	update();
	emit posChanged(delta);
}

QList<QPointF> xRegCircle::controlPoints() const
{
	return { pt1(), pt2(), pt3() };
}

void xRegCircle::moveCtrlPoint(const QPointF &pt, const QPointF &movedPt)
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

bool xRegCircle::isCtrlPoint(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	return (Distance(pt1(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt2(), p) < DELTA_DIST_2 / viewScaleFactor()
		|| Distance(pt3(), p) < DELTA_DIST_2 / viewScaleFactor());
}

void xRegCircle::changeEdgeByPoint(const QPointF &p)
{
	const qreal dw = fabs(Distance(p, m_regCircle.center()) - m_regCircle.radius());
	setRegWidth(dw);
}

bool xRegCircle::isRegionEdge(const QPointF &p) const
{
	if (!(flags() & ItemIsMovable))
		return false;

	const qreal dw = fabs(Distance(p, m_regCircle.center()) - m_regCircle.radius());
	if (fabs(dw - m_width) < DELTA_DIST_2 / viewScaleFactor())
		return true;
	return false;
}
