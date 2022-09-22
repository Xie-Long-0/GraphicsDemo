#include "xActionDrawRegArc.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xRegArc.h"
#include "entity/xLine.h"

xActionDrawRegArc::xActionDrawRegArc(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawRegArc)
{
}

xActionDrawRegArc::~xActionDrawRegArc()
{
	if (!isFinished())
		cancel();
}

void xActionDrawRegArc::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		auto spos = viewMapToScene(e);
		switch (m_status)
		{
		case xDef::AS_Default:
			mp1 = spos;
			m_status = xDef::AS_DrawEntity1_P1;
			e->accept();
			break;

		case xDef::AS_DrawEntity1_P1:
			if (Distance(mp1, spos) > DELTA_DIST_2)
			{
				mp2 = spos;
				m_line->setLine(mp1, mp2);
				m_status = xDef::AS_DrawEntity1_P2;
				e->accept();
			}
			break;

		case xDef::AS_DrawEntity1_P2:
			if (Distance(mp1, spos) > DELTA_DIST_2 && Distance(mp2, spos) > DELTA_DIST_2)
			{
				m_arc->setArc(mp1, mp2, viewMapToScene(e), 30);
				m_arc->setStyle(xDef::S_RegDrawn);
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

void xActionDrawRegArc::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		// 画两个点时显示为画直线
		if (m_line == nullptr)
		{
			m_line = new xLine(m_view);
			m_line->setStyle(xDef::S_Drawing);
			m_scene->addItem(m_line);
		}
		m_line->setLine(mp1, viewMapToScene(e));
		e->accept();
		break;

	case xDef::AS_DrawEntity1_P2:
		// 画第三个点时删除临时的直线
		if (m_line)
		{
			m_scene->removeItem(m_line);
			m_line->deleteLater();
			m_line = nullptr;
		}
		if (m_arc == nullptr)
		{
			m_arc = new xRegArc(m_view);
			m_arc->setStyle(xDef::S_RegDrawing);
			m_scene->addItem(m_arc);
		}
		m_arc->setArc(mp1, mp2, viewMapToScene(e), 30);
		e->accept();
		break;

	default:
		break;
	}
}

void xActionDrawRegArc::mouseReleaseEvent(QMouseEvent *e)
{
}

void xActionDrawRegArc::cancel()
{
	if (m_line)
	{
		m_scene->removeItem(m_line);
		m_line->deleteLater();
		m_line = nullptr;
	}
	if (m_arc)
	{
		m_scene->removeItem(m_arc);
		m_arc->deleteLater();
		m_arc = nullptr;
	}
	m_status = xDef::AS_Default;
}
