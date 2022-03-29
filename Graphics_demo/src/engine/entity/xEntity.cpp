#include "xEntity.h"

xEntity::xEntity(xGraphicView *view, QGraphicsItem *parent)
	: QGraphicsItem(parent)
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
	m_style = xStyle::NoStyle;	// ��������ʽ��ʹ���ֶ����õıʻ�
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
