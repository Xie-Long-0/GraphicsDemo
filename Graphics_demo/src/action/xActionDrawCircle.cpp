#include "xActionDrawCircle.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xCircle.h"
#include "entity/xLine.h"

xActionDrawCircle::xActionDrawCircle(xGraphicView *view, QObject *parent)
	: xActionInterface(view, parent, xDef::AT_DrawCircle)
{
}

xActionDrawCircle::~xActionDrawCircle()
{
}

void xActionDrawCircle::mousePressEvent(QMouseEvent *e)
{
	auto spos = pointMapToScene(e);
	m_processed = false;
	if (e->button() == Qt::LeftButton)
	{
		switch (m_status)
		{
		case xDef::S_Default:
			p1 = spos;
			m_status = xDef::S_DrawEntity1_Start;
			m_processed = true;
			break;

		case xDef::S_DrawEntity1_Start:
			if (QLineF(p1, spos).length() > 10)
			{
				p2 = spos;
				m_status = xDef::S_DrawEntity1_P2;
				m_processed = true;
			}
			break;

		case xDef::S_DrawEntity1_P2:
			if (QLineF(p1, spos).length() > 10 && QLineF(p2, spos).length() > 10)
			{
				m_circle->setStyle(xStyle::Drawn);
				m_status = xDef::S_DrawEntity1_End;
				m_processed = true;
			}
			break;

		case xDef::S_DrawEntity1_End:
			//p1 = spos;
			//if (m_circle == nullptr)
			//{
			//	m_circle = new xCircle();
			//	m_scene->addItem(m_circle);
			//}
			//if (QLineF(p1, m_line->pt1()).length() < 6)
			//{
			//	m_isGrabCtrlPoint = true;
			//	m_moveP1 = true;
			//	m_processed = true;
			//}
			//else if (QLineF(p1, m_line->pt2()).length() < 6)
			//{
			//	m_isGrabCtrlPoint = true;
			//	m_moveP2 = true;
			//	m_processed = true;
			//}
			break;

		case xDef::S_DrawFinished:
		case xDef::S_ActionFinished:
		default:
			break;
		}
	}
}

void xActionDrawCircle::mouseMoveEvent(QMouseEvent *e)
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
		m_line->setLine(p1, pointMapToScene(e));
		m_processed = true;
		break;

	case xDef::S_DrawEntity1_P2:
		if (m_line)
		{
			m_scene->removeItem(m_line);
			delete m_line;
			m_line = nullptr;
		}
		if (m_circle == nullptr)
		{
			m_circle = new xCircle();
			m_circle->setStyle(xStyle::Drawing);
			m_scene->addItem(m_circle);
		}
		m_circle->setCircle(xCircleData(p1, p2, pointMapToScene(e)));
		m_processed = true;
		break;

	case xDef::S_DrawEntity1_End:
		break;
	case xDef::S_DrawFinished:
		break;
	case xDef::S_ActionFinished:
		break;
	default:
		break;
	}
}

void xActionDrawCircle::mouseReleaseEvent(QMouseEvent *e)
{
	m_isGrabCtrlPoint = false;
	m_processed = false;
}
