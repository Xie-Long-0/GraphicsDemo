#include "xInterArc.h"
#include "xArc.h"
#include "xRegArc.h"
#include <QFontMetrics>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QThread>

#include "RecognizeHandler.h"

xInterArc::xInterArc(xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(view, parent)
{
}

xInterArc::xInterArc(xArc *item, xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(view, parent)
{
	bindEntity(item);
}

xInterArc::xInterArc(xRegArc *item, xGraphicView *view, QGraphicsItem *parent)
	: xInterSingleEntity(view, parent)
{
	bindEntity(item);
}

int xInterArc::type() const
{
	return Type;
}

void xInterArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(widget);

	auto style = m_style;
	const qreal f = viewScaleFactor();
	if (style != xDef::S_NoStyle)
	{
		// ѡ��״̬
		if (isSelected())
		{
			style = xDef::S_TxtSelected;
			if (m_bindEntity)
				m_bindEntity->setSelected(true);
		}

		// ��ͣ״̬
		if (option->state & QStyle::State_MouseOver)
		{
			style = xDef::S_TxtHovered;
		}

		MakeStyle(style, &m_pen, nullptr, f);
	}

	// ������
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	// �߾�
	const qreal m = m_pen.widthF() + 4 / f;

	// ���Ÿı�ʱ���������С
	if (!qFuzzyCompare(m_lastFactor, f))
	{
		m_lastFactor = f;
		// ���������С
		m_font.setPointSizeF(FontSize / f);

		QFontMetricsF fm(m_font);
		m_textRect = fm.boundingRect(m_text);
		// ����ԭ���Ƶ��ױ�����
		m_textRect.translate(-m_textRect.bottomLeft());
		m_textRect.translate(-m_textRect.width() / 2, 0);
	}

	// �����ӵ�����
	painter->setPen(QPen(m_pen.color(), m_pen.widthF(), Qt::DashLine));
	painter->drawLine(linkL);

	// ת���滭����ϵ
	painter->translate(m_bindPoint);
	painter->rotate(m_rotateAngle);
	painter->translate(m_shiftDist, -linkL.length());

	painter->setPen(m_pen);
	painter->drawLine(m_textRect.bottomLeft() + QPointF(-m, 0), m_textRect.bottomRight() + QPointF(m, 0));
	// ���ı����ݣ���������ӵ��滭·���ɵõ���ƽ��������
	QPainterPath path;
	path.addText(m_textRect.left(), m_textRect.bottom() - m, m_font, m_text);
	painter->drawPath(path);
}

QRectF xInterArc::boundingRect() const
{
	if (m_bindEntity == nullptr)
		return QRectF();

	// ������
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	const qreal m = m_pen.widthF() * 2 + 4 / viewScaleFactor();

	// �߽����
	QRectF rect = m_textRect.marginsAdded({ m,0,m,m });
	// �Ƶ��󶨵��Ϸ�
	rect.translate(m_bindPoint);
	rect.translate(m_shiftDist, -linkL.length());
	// Ӧ����ת���󣬵õ�������ת�����Ӿ���
	rect = m_transform.mapRect(rect);

	// ���߽�������󵽰󶨵�λ��
	if (m_bindPoint.x() < rect.left() + m)
	{
		rect.setLeft(m_bindPoint.x() - m);
	}
	else if (m_bindPoint.x() > rect.right() - m)
	{
		rect.setRight(m_bindPoint.x() + m);
	}

	if (m_bindPoint.y() < rect.top() + m)
	{
		rect.setTop(m_bindPoint.y() - m);
	}
	else if (m_bindPoint.y() > rect.bottom() - m)
	{
		rect.setBottom(m_bindPoint.y() + m);
	}

	return rect;
}

QPainterPath xInterArc::shape() const
{
	if (m_bindEntity == nullptr)
		return QPainterPath();

	// ������
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	const qreal m = m_pen.widthF() * 2;

	// ʹ�ö���δ������ֿ���Σ��������ֻ滭·�������Ч��
	QPolygonF pg(m_textRect.marginsAdded({ m,0,m,m }));
	// �Ƶ��󶨵��Ϸ�
	pg.translate(m_bindPoint);
	pg.translate(m_shiftDist, -linkL.length());

	QPainterPath path;
	// �����ת��Ķ����
	path.addPolygon(m_transform.map(pg));
	return path;
}

void xInterArc::bindEntity(xEntity *e)
{
	xInterSingleEntity::bindEntity(e);
	if (e->type() == xArc::Type)
	{
		auto c = static_cast<xArc *>(e);
		setBindPoint(c->center());
	}
	else if (e->type() == xRegArc::Type)
	{
		auto c = static_cast<xRegArc *>(e);
		setBindPoint(c->center());
	}
}

void xInterArc::calculate()
{
	QThread *td = new QThread;
	RecognizeHandler *rh = new RecognizeHandler;
	rh->moveToThread(td);
	connect(td, &QThread::finished, td, &QObject::deleteLater);
	connect(td, &QThread::finished, rh, &QObject::deleteLater);
	connect(rh, &RecognizeHandler::calcDone, td, &QThread::quit);
	connect(rh, &RecognizeHandler::calcDone, m_view, &xGraphicView::calcFinished);
	connect(td, &QThread::started, this, [=]() { rh->calcArc(this); });
	td->start();
}

void xInterArc::onEntityChanged()
{
	if (m_bindEntity->type() == xArc::Type)
	{
		auto i = static_cast<xArc *>(m_bindEntity);
		setBindPoint(i->center());
	}
	else if (m_bindEntity->type() == xRegArc::Type)
	{
		auto i = static_cast<xRegArc *>(m_bindEntity);
		setBindPoint(i->center());
	}
}
