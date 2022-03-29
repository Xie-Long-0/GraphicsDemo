#include "xActionDefault.h"
#include <QMouseEvent>
#include "xGraphicView.h"
#include "xEntity.h"

xActionDefault::xActionDefault(xGraphicView *view)
	: xActionInterface(view, xDef::AT_Default)
{
}

xActionDefault::~xActionDefault()
{
}

void xActionDefault::mousePressEvent(QMouseEvent *e)
{
	m_p = pointMapToScene(e);
	if (e->button() == Qt::LeftButton)
	{
		auto item = static_cast<xEntity *>(m_view->itemAt(e->pos()));
		if (item && (item->flags() & QGraphicsItem::ItemIsMovable))
		{
			// 判断是否选中控制点
			if (item->isCtrlPoint(m_p))
			{
				m_isGrabCtrlPoint = true;
				m_item = item;
				e->accept();
			}
		}
	}
}

void xActionDefault::mouseMoveEvent(QMouseEvent *e)
{
	if (m_isGrabCtrlPoint && m_item)
	{
		// 移动控制点
		auto p = pointMapToScene(e);
		m_item->moveCtrlPoint(m_p, p);
		e->accept();
		m_p = p;
	}
}

void xActionDefault::mouseReleaseEvent(QMouseEvent *e)
{
	m_isGrabCtrlPoint = false;
	m_item = nullptr;
}
