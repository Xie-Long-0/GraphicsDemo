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
	if (e->button() == Qt::LeftButton)
	{
		// 获取鼠标位置的图元
		auto gi = m_view->itemAt(e->pos());
		if (gi == nullptr || gi->type() <= xEntity::ET_Unknown)
			return;

		auto item = static_cast<xEntity *>(gi);
		m_p = viewMapToScene(e);

		if (item->flags() & QGraphicsItem::ItemIsSelectable && item->parentItem() == nullptr)
		{
			// 将当前图元堆叠在与其相撞的其它图元上面
			auto others = item->collidingItems();
			for (auto i : others)
			{
				if (i->parentItem())
					continue;
				i->stackBefore(item);
			}
		}

		// 判断是否选中控制点
		if (item->isCtrlPoint(m_p))
		{
			m_isGrabCtrlPoint = true;
			m_item = item;
			return;
		}
		// 判断是否属于Region类型
		if (item->type() > xEntity::ET_Region_Start && item->type() < xEntity::ET_Region_End)
		{
			// 判断是否选中范围边缘
			auto ri = static_cast<xRegionEntity *>(gi);
			if (ri->isRegionEdge(m_p))
			{
				m_isGrabRegionEdge = true;
				m_item = ri;
				return;
			}
		}
		// 判断是否移动图元
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
	// 移动控制点
	if (m_isGrabCtrlPoint && m_item)
	{
		auto p = viewMapToScene(e);
		m_item->moveCtrlPoint(m_p, p);
		m_p = p;
		m_itemChanged = true;
		e->accept();
		return;
	}
	// 移动范围
	if (m_isGrabRegionEdge && m_item)
	{
		auto p = viewMapToScene(e);
		static_cast<xRegionEntity *>(m_item)->changeEdgeByPoint(p);
		m_itemChanged = true;
		e->accept();
		return;
	}
	// 移动图元
	if (m_willMoveItem && m_item)
	{
		auto p = viewMapToScene(e);
		m_item->moveBy(p - m_p);
		m_p = p;
		m_itemChanged = true;
		e->accept();
		return;
	}
}

void xActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_itemChanged && m_item)
		{
			// 移动后对需要重新计算的图形执行计算任务
			if (m_item->needCalculate())
				m_item->requestCalc();
		}
		m_willMoveItem = false;
		m_isGrabCtrlPoint = false;
		m_isGrabRegionEdge = false;
		m_itemChanged = false;
		m_item = nullptr;
	}
	else
	{
		e->accept();
	}
}
