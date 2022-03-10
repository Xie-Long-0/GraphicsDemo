#include "xActionDrawLine.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xLine.h"

xActionDrawLine::xActionDrawLine(xGraphicView *view, QObject *parent)
	: xActionInterface(view, parent, xDef::AT_DrawLine)
{
}

xActionDrawLine::~xActionDrawLine()
{
}

void xActionDrawLine::mousePressEvent(QMouseEvent *e)
{
	auto spos = pointMapToScene(e);
	m_processed = false;
	if (e->button() == Qt::LeftButton)
	{
		switch (m_status)
		{
		case xDef::S_Default:
			mp = spos;
			m_status = xDef::S_DrawEntity1_Start;
			m_processed = true;
			break;

		case xDef::S_DrawEntity1_Start:
			if (QLineF(mp, spos).length() > 10)
			{
				if (m_line == nullptr)
				{
					m_line = new xLine();
					m_scene->addItem(m_line);
				}
				m_line->setLine(mp, spos);
				m_line->setStyle(xStyle::Drawn);
				m_status = xDef::S_DrawEntity1_End;
				m_processed = true;
			}
			break;

		case xDef::S_DrawEntity1_End:
			mp = spos;
			if (QLineF(mp, m_line->pt1()).length() < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP1 = true;
				m_processed = true;
			}
			else if (QLineF(mp, m_line->pt2()).length() < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP2 = true;
				m_processed = true;
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
	m_processed = false;
	switch (m_status)
	{
	case xDef::S_DrawEntity1_Start:
		if (m_line == nullptr)
		{
			m_line = new xLine();
			m_line->setStyle(xStyle::Drawing);
			m_scene->addItem(m_line);
		}
		m_line->setLine(mp, pointMapToScene(e));
		m_processed = true;
		break;

	case xDef::S_DrawEntity1_End:
		if (m_moveP1)
		{
			m_line->setPt1(pointMapToScene(e));
			m_processed = true;
		}
		else if (m_moveP2)
		{
			m_line->setPt2(pointMapToScene(e));
			m_processed = true;
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
	m_processed = false;
}
