#include "xEntity.h"
#include <QGraphicsSceneMouseEvent>

xEntity::xEntity(xGraphicView *view, QGraphicsItem *parent)
	: QGraphicsObject(parent)
	, m_view(view)
{
	init();
}

void xEntity::setPen(const QPen &pen)
{
	if (pen == m_pen)
		return;

	prepareGeometryChange();
	m_pen = pen;
	m_style = xStyle::NoStyle;	// 设置无样式以使用手动设置的笔画
	update();
}

void xEntity::setStyle(xStyle::Style style)
{
	if (style == m_style)
		return;

	prepareGeometryChange();
	m_style = style;
	update();
}

QVariant xEntity::itemChange(GraphicsItemChange change, const QVariant &value)
{
	switch (change)
	{
	case QGraphicsItem::ItemSelectedChange:
		break;
	case QGraphicsItem::ItemSelectedHasChanged:
		emit selectedChanged(value.toBool());
		break;
	case QGraphicsItem::ItemCursorChange:
		break;
	case QGraphicsItem::ItemCursorHasChanged:
		emit cursorChanged(value.value<QCursor>());
		break;
	case QGraphicsItem::ItemFlagsChange:
		break;
	case QGraphicsItem::ItemFlagsHaveChanged:
		emit flagsChanged(GraphicsItemFlags(value.value<quint32>()));
		break;
	default:
		break;
	}
	return value;
}

void xEntity::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
	if ((e->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable))
		moveBy(e->scenePos());
}
