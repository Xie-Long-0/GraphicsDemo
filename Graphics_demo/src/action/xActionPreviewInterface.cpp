#include "xActionPreviewInterface.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

xActionPreviewInterface::xActionPreviewInterface(xGraphicView *view, xDef::ActionType type)
	: xActionInterface(view, type)
{
	// 所有实体禁止移动、选中与悬停事件
	auto items = m_scene->items();
	for (auto i : items)
	{
		i->setFlag(QGraphicsItem::ItemIsMovable, false);
		i->setFlag(QGraphicsItem::ItemIsSelectable, false);
		i->setAcceptHoverEvents(false);
	}
}

xActionPreviewInterface::~xActionPreviewInterface()
{
	// 所有实体取消禁止移动、选中与悬停事件
	auto items = m_scene->items();
	for (auto i : items)
	{
		// 跳过图片实体
		if (i->type() == QGraphicsPixmapItem::Type)
			continue;
		i->setFlag(QGraphicsItem::ItemIsMovable, true);
		i->setFlag(QGraphicsItem::ItemIsSelectable, true);
		i->setAcceptHoverEvents(true);
	}
}

void xActionPreviewInterface::confirm()
{
	m_status = xDef::S_ActionFinished;
}

bool xActionPreviewInterface::isFinished() const
{
	return (m_status >= xDef::S_ActionFinished);
}
