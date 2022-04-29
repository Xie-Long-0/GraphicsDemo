#include "xInterCircle.h"
#include "xCircle.h"
#include "xRegCircle.h"
#include <QFontMetrics>

xInterCircle::xInterCircle(xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(view, parent)
{
}

xInterCircle::xInterCircle(xCircle *item, xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(item, view, parent)
{
	m_bindPoint = item->center();
}

xInterCircle::xInterCircle(xRegCircle *item, xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(item, view, parent)
{
	m_bindPoint = item->center();
}

xInterCircle::~xInterCircle()
{
}

int xInterCircle::type() const
{
	return Type;
}

void xInterCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

QRectF xInterCircle::boundingRect() const
{
	return QRectF();
}

QPainterPath xInterCircle::shape() const
{
	QPainterPath path;

	path.moveTo(m_bindPoint);
	path.lineTo(m_anchorPoint);

	qreal angle = AnglePoint2Point(m_bindPoint, m_anchorPoint) - M_PI_2;
	QFont font;
	font.setPointSizeF(10);
	
	QFontMetricsF fm(font);
	QRectF text_rect = fm.boundingRect(m_text);
	QPolygonF rp(text_rect);
	
	QTransform tf;
	
	return path;
}

void xInterCircle::onEntityChanged()
{
}
