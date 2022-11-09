#include "xActionDrawRegRect.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "xGraphicView.h"
#include "xRegRect.h"

xActionDrawRegRect::xActionDrawRegRect(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawRegRect)
{
}

xActionDrawRegRect::~xActionDrawRegRect()
{
	if (!isFinished())
		cancel();
}

void xActionDrawRegRect::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		const auto spos = viewMapToScene(e);
		switch (m_status)
		{
		case xDef::AS_Default:
			mp = spos;
			m_status = xDef::AS_DrawEntity1_P1;
			e->accept();
			break;

		case xDef::AS_DrawEntity1_P1:
			if (Distance(mp, spos) > DELTA_DIST_2)
			{
				m_rect->setRect(mp, spos);
				m_rect->setStyle(xDef::S_RegDrawn);
				// 操作完成，设置为AS_ActionFinished
				m_status = xDef::AS_ActionFinished;
				e->accept();
			}
			break;

		default:
			break;
		}
	}
}

void xActionDrawRegRect::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		if (Distance(mp, viewMapToScene(e)) > DELTA_DIST_2)
		{
			if (m_rect == nullptr)
			{
				m_rect = new xRegRect(m_view);
				m_rect->setStyle(xDef::S_RegDrawing);
				m_scene->addItem(m_rect);
			}
			m_rect->setRect(mp, viewMapToScene(e));
			e->accept();
		}
		break;

	default:
		break;
	}
}

void xActionDrawRegRect::mouseReleaseEvent(QMouseEvent *e)
{
}

void xActionDrawRegRect::cancel()
{
	if (m_rect)
	{
		m_scene->removeItem(m_rect);
		m_rect->deleteLater();
		m_rect = nullptr;
	}
	m_status = xDef::AS_Default;
}
