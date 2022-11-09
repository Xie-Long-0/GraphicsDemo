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

int xInterArc::type() const noexcept
{
	return Type;
}

void xInterArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (painter == nullptr)
    {
        qWarning() << __FUNCTION__ << "painter is a nullptr!";
        return;
    }
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
		m_font.setPointSizeF(FontSize / f);

		QFontMetricsF fm(m_font);
		m_textRect = fm.boundingRect(m_text);
		// 矩形原点移到底边中心
		m_textRect.translate(-m_textRect.bottomLeft());
		m_textRect.translate(-m_textRect.width() / 2, 0);
	}

	// 画连接的虚线
	painter->setPen(QPen(m_pen.color(), m_pen.widthF(), Qt::DashLine));
	painter->drawLine(linkL);

	// 转换绘画坐标系
	painter->translate(m_bindPoint);
	painter->rotate(m_rotateAngle);
	painter->translate(m_shiftDist, -linkL.length());

	painter->setPen(m_pen);
	painter->drawLine(m_textRect.bottomLeft() + QPointF(-m, 0), m_textRect.bottomRight() + QPointF(m, 0));
	// 画文本内容，将文字添加到绘画路径可得到更平整的文字
	QPainterPath path;
	path.addText(m_textRect.left(), m_textRect.bottom() - m, m_font, m_text);
	painter->drawPath(path);
}

QRectF xInterArc::boundingRect() const
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

void xInterArc::bindEntity(xEntity *e)
{
    if (e == nullptr)
    {
        qWarning() << __FUNCTION__ << "entity is a nullptr!";
        return;
    }

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
