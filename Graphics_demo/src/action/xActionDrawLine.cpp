#include "xActionDrawLine.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xLine.h"

xActionDrawLine::xActionDrawLine(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawLine)
{
}

xActionDrawLine::~xActionDrawLine()
{
}

void xActionDrawLine::mousePressEvent(QMouseEvent *e)
{
	auto spos = pointMapToScene(e);
	if (e->button() == Qt::LeftButton)
	{
		switch (m_status)
		{
		case xDef::S_Default:
			mp = spos;
			m_status = xDef::S_DrawEntity1_P1;
			e->accept();
			break;

		case xDef::S_DrawEntity1_P1:
			if (Distance(mp, spos) > 10)
			{
				if (m_line == nullptr)
				{
					m_line = new xLine(m_view);
					m_scene->addItem(m_line);
				}
				m_line->setLine(mp, spos);
				m_line->setStyle(xStyle::Drawn);
				m_status = xDef::S_ActionFinished;
				e->accept();
			}
			break;

		case xDef::S_DrawEntity1_P2:
			mp = spos;
			if (Distance(mp, m_line->pt1()) < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP1 = true;
				e->accept();
			}
			else if (Distance(mp, m_line->pt2()) < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP2 = true;
				e->accept();
			}
			break;

		case xDef::S_DrawFinished:
		case xDef::S_ActionFinished:
		default:
			break;
		}
	}
}

void xActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::S_DrawEntity1_P1:
		if (m_line == nullptr)
		{
			m_line = new xLine(m_view);
			m_line->setStyle(xStyle::Drawing);
			m_scene->addItem(m_line);
		}
		m_line->setLine(mp, pointMapToScene(e));
		e->accept();
		break;

	case xDef::S_DrawEntity1_P2:
		if (m_moveP1)
		{
			m_line->setPt1(pointMapToScene(e));
			e->accept();
		}
		else if (m_moveP2)
		{
			m_line->setPt2(pointMapToScene(e));
			e->accept();
		}
		break;

	case xDef::S_DrawFinished:
	default:
		break;
	}
}

void xActionDrawLine::mouseReleaseEvent(QMouseEvent *e)
{
	m_isGrabCtrlPoint = false;
	m_moveP1 = false;
	m_moveP2 = false;
}

void xActionDrawLine::cancel()
{
	if (m_line)
	{
		m_scene->removeItem(m_line);
		delete m_line;
		m_line = nullptr;
	}
	m_status = xDef::S_Default;
}
