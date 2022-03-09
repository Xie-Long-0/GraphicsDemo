#include "xActionDrawLine.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xLine.h"

xActionDrawLine::xActionDrawLine(QGraphicsScene *scene, xGraphicView *view, QObject *parent)
	: xActionInterface(scene, view, parent, xDef::AT_DrawLine)
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
		switch (status())
		{
		case xDef::S_Default:
			p1 = spos;
			setStatus(xDef::S_DrawEntity1_Start);
			m_processed = true;
			break;

		case xDef::S_DrawEntity1_Start:
			p2 = spos;
			if (tempLine == nullptr)
			{
				tempLine = new xLine();
				m_scene->addItem(tempLine);
			}
			tempLine->setLine(p1, p2);
			tempLine->setStyle(xStyle::Drawn);
			setStatus(xDef::S_DrawEntity1_End);
			m_processed = true;
			break;

		case xDef::S_DrawEntity1_End:
			p1 = spos;
			if (QLineF(p1, tempLine->pt1()).length() < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP1 = true;
				m_processed = true;
			}
			else if (QLineF(p1, tempLine->pt2()).length() < 6)
			{
				m_isGrabCtrlPoint = true;
				m_moveP2 = true;
				m_processed = true;
			}
			break;

		case xDef::S_DrawFinished:
		case xDef::S_Measured:
		case xDef::S_ActionFinished:
		default:
			break;
		}
	}
	else if (e->button() == Qt::RightButton)
	{
		switch (status())
		{
		case xDef::S_DrawEntity1_Start:
			break;
		case xDef::S_DrawEntity1_End:
			break;
		case xDef::S_DrawEntity2_Start:
			break;
		case xDef::S_DrawEntity2_End:
			break;
		case xDef::S_DrawFinished:
			break;
		case xDef::S_Measured:
			break;
		case xDef::S_ActionFinished:
			break;
		default:
			break;
		}
	}
}

void xActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{
	m_processed = false;
	switch (status())
	{
	case xDef::S_DrawEntity1_Start:
		p2 = pointMapToScene(e);
		if (tempLine == nullptr)
		{
			tempLine = new xLine();
			tempLine->setStyle(xStyle::Drawing);
			m_scene->addItem(tempLine);
		}
		tempLine->setLine(p1, p2);
		m_processed = true;
		break;

	case xDef::S_DrawEntity1_End:
		if (m_moveP1)
		{
			tempLine->setPt1(pointMapToScene(e));
			m_processed = true;
		}
		else if (m_moveP2)
		{
			tempLine->setPt2(pointMapToScene(e));
			m_processed = true;
		}
		break;

	case xDef::S_DrawFinished:
	case xDef::S_Measured:
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
