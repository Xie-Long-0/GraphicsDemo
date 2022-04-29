#include "xActionPreviewInterface.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

xActionPreviewInterface::xActionPreviewInterface(xGraphicView *view, xDef::ActionType type)
	: xActionInterface(view, type)
{
	// ����ʵ���ֹ�ƶ���ѡ������ͣ�¼�
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
	// ����ʵ��ȡ����ֹ�ƶ���ѡ������ͣ�¼�
	auto items = m_scene->items();
	for (auto i : items)
	{
		// ����ͼƬʵ��
		if (i->type() == QGraphicsPixmapItem::Type)
			continue;
		if (i->parentItem() == nullptr)
			i->setFlag(QGraphicsItem::ItemIsMovable, true);
		i->setFlag(QGraphicsItem::ItemIsSelectable, true);
		i->setAcceptHoverEvents(true);
	}
}

void xActionPreviewInterface::confirm()
{
}

bool xActionPreviewInterface::isFinished() const
{
	return (m_status >= xDef::AS_ActionFinished);
}
