#include "xInterCircle.h"
#include "xCircle.h"
#include "xRegCircle.h"
#include <QFontMetrics>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QThread>

#include "RecognizeHandler.h"

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
	Q_UNUSED(widget);

	auto style = m_style;
	const qreal f = viewScaleFactor();
	if (style != xDef::S_NoStyle)
	{
		// 选中状态
		if (isSelected())
		{
			style = xDef::S_TxtSelected;
			if (m_bindEntity)
				m_bindEntity->setSelected(true);
		}

		// 悬停状态
		if (option->state & QStyle::State_MouseOver)
		{
			style = xDef::S_TxtHovered;
		}

		MakeStyle(style, &m_pen, nullptr, f);
	}

	// 连接线
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	// 边距
	const qreal m = m_pen.widthF() + 4 / f;

	// 缩放改变时更新字体大小
	if (!qFuzzyCompare(m_lastFactor, f))
	{
		m_lastFactor = f;
		// 更新字体大小
		m_font.setPointSizeF(11.0 / f);
		m_font.setWeight(QFont::ExtraLight);

		QFontMetricsF fm(m_font);
		m_textRect = fm.boundingRect(m_text);
		// 矩形原点移到底边中心
		m_textRect.translate(-m_textRect.bottomLeft());
		m_textRect.translate(-m_textRect.width() / 2, 0);
	}

	// TODO: 后续优化文字旋转与绘画，提升性能
	QPainterPath path;
	// 添加文本底线
	path.moveTo(m_textRect.bottomLeft() + QPointF(-4 / f, 0));
	path.lineTo(m_textRect.bottomRight() + QPointF(4 / f, 0));
	// 添加文字
	path.addText(m_textRect.left(), m_textRect.bottom() - m, m_font, m_text);
	// 移动并旋转
	path.translate(m_bindPoint);
	path.translate(m_shiftDist, -linkL.length());
	path = m_transform.map(path);

	// 画连接的虚线
	painter->setPen(QPen(m_pen.color(), m_pen.widthF(), Qt::DashLine));
	painter->drawLine(linkL);
	// 画文本内容
	painter->setPen(m_pen);
	painter->drawPath(path);
}

QRectF xInterCircle::boundingRect() const
{
	if (m_bindEntity == nullptr)
		return QRectF();

	// 连接线
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	const qreal m = m_pen.widthF() * 2 + 4 / viewScaleFactor();

	// 边界矩形
	QRectF rect = m_textRect.marginsAdded({ m,0,m,m });
	// 移到绑定点上方
	rect.translate(m_bindPoint);
	rect.translate(m_shiftDist, -linkL.length());
	// 应用旋转矩阵，得到矩形旋转后的外接矩形
	rect = m_transform.mapRect(rect);

	// 将边界矩形扩大到绑定点位置
	if (m_bindPoint.x() < rect.left())
	{
		rect.setLeft(m_bindPoint.x());
	}
	else if (m_bindPoint.x() > rect.right())
	{
		rect.setRight(m_bindPoint.x());
	}

	if (m_bindPoint.y() < rect.top())
	{
		rect.setTop(m_bindPoint.y());
	}
	else if (m_bindPoint.y() > rect.bottom())
	{
		rect.setBottom(m_bindPoint.y());
	}

	return rect;
}

QPainterPath xInterCircle::shape() const
{
	if (m_bindEntity == nullptr)
		return QPainterPath();

	// 连接线
	const QLineF linkL(m_bindPoint, m_anchorPoint);
	const qreal m = m_pen.widthF() * 2;

	// 使用多边形处理文字框矩形，代替文字绘画路径，提高效率
	QPolygonF pg(m_textRect.marginsAdded({ m,0,m,m }));
	// 移到绑定点上方
	pg.translate(m_bindPoint);
	pg.translate(m_shiftDist, -linkL.length());
	
	QPainterPath path;
	// 添加旋转后的多边形
	path.addPolygon(m_transform.map(pg));
	return path;
}

void xInterCircle::bindEntity(xEntity *e)
{
	xInterSingleEntity::bindEntity(e);
	if (e->type() == xCircle::Type)
	{
		auto c = static_cast<xCircle *>(e);
		setBindPoint(c->center());
	}
	else if (e->type() == xRegCircle::Type)
	{
		auto c = static_cast<xRegCircle *>(e);
		setBindPoint(c->center());
	}
}

void xInterCircle::onEntityChanged()
{
	if (m_bindEntity->type() == xCircle::Type)
	{
		setBindPoint(static_cast<xCircle *>(m_bindEntity)->center());
	}
	else if (m_bindEntity->type() == xRegCircle::Type)
	{
		setBindPoint(static_cast<xRegCircle *>(m_bindEntity)->center());
	}
}

void xInterCircle::calculate()
{
	QThread *td = new QThread;
	RecognizeHandler *rh = new RecognizeHandler;
	rh->moveToThread(td);
	connect(td, &QThread::finished, td, &QObject::deleteLater);
	connect(td, &QThread::finished, rh, &QObject::deleteLater);
	connect(rh, &RecognizeHandler::calcDone, td, &QThread::quit);
	connect(rh, &RecognizeHandler::calcDone, m_view, &xGraphicView::calcFinished);
	connect(td, &QThread::started, this, [=]() { rh->calcCircle(this); });
	td->start();
}
