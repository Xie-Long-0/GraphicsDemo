#include "xActionDefault.h"
#include <QMouseEvent>
#include <QDebug>
#include "xGraphicView.h"
#include "xRegionEntity.h"

xActionDefault::xActionDefault(xGraphicView *view)
	: xActionInterface(view, xDef::AT_Default)
{
}

xActionDefault::~xActionDefault()
{
}

void xActionDefault::mousePressEvent(QMouseEvent *e)
{
	m_p = viewMapToScene(e);
	if (e->button() == Qt::LeftButton)
	{
		auto gi = m_view->itemAt(e->pos());
		if (gi == nullptr || gi->type() <= xEntity::ET_Unknown)
			return;

		auto item = static_cast<xEntity *>(gi);

		if (item->flags() & QGraphicsItem::ItemIsSelectable)
		{
			// ����ǰͼԪ�ѵ���������ײ������ͼԪ����
			auto others = item->collidingItems();
			for (auto i : others)
			{
				i->stackBefore(item);
			}
		}

		// �ж��Ƿ�ѡ�п��Ƶ�
		if (item->isCtrlPoint(m_p))
		{
			m_isGrabCtrlPoint = true;
			m_item = item;
			return;
		}
		// �ж��Ƿ�����Region����
		if (item->type() > xEntity::ET_Region_Start && item->type() < xEntity::ET_Region_End)
		{
			// �ж��Ƿ�ѡ�з�Χ��Ե
			auto ri = static_cast<xRegionEntity *>(gi);
			if (ri->isRegionEdge(m_p))
			{
				m_isGrabRegionEdge = true;
				m_item = ri;
				return;
			}
		}
		// �ж��Ƿ��ƶ�ͼԪ
		if (item->flags() & QGraphicsItem::ItemIsMovable)
		{
			m_willMoveItem = true;
			m_item = item;
			return;
		}
	}
	else
	{
		e->accept();
	}
}

void xActionDefault::mouseMoveEvent(QMouseEvent *e)
{
	// �ƶ����Ƶ�
	if (m_isGrabCtrlPoint && m_item)
	{
		auto p = viewMapToScene(e);
		m_item->moveCtrlPoint(m_p, p);
		m_p = p;
		e->accept();
		return;
	}
	// �ƶ���Χ
	if (m_isGrabRegionEdge && m_item)
	{
		auto p = viewMapToScene(e);
		static_cast<xRegionEntity *>(m_item)->changeEdgeByPoint(p);
		e->accept();
		return;
	}
	// �ƶ�ͼԪ
	if (m_willMoveItem && m_item)
	{
		auto p = viewMapToScene(e);
		m_item->moveBy(p - m_p);
		m_p = p;
		e->accept();
		return;
	}
}

void xActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_willMoveItem = false;
		m_isGrabCtrlPoint = false;
		m_isGrabRegionEdge = false;
		m_item = nullptr;
	}
	else
	{
		e->accept();
	}
}
