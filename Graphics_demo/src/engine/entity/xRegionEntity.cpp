#include "xRegionEntity.h"

xRegionEntity::xRegionEntity(xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
{
	m_hasChild = true;
}

xRegionEntity::xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent)
	: xEntity(view, parent)
	, m_width(width)
{
	m_hasChild = true;
}

xRegionEntity::~xRegionEntity()
{
}

void xRegionEntity::setRegWidth(qreal w)
{
	if (qFuzzyCompare(w, m_width))
		return;

	prepareGeometryChange();
	m_width = w;
	update();
	emit regWidthChanged(w);
}

void xRegionEntity::setBrush(const QBrush &brush)
{
	if (brush == m_brush)
		return;

	prepareGeometryChange();
	m_brush = brush;
	m_style = xDef::S_NoStyle;	// 设置无样式以使用自定义笔刷
	update();
}
