#include "xActionDrawRegCircle.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "engine/xGraphicView.h"
#include "entity/xRegCircle.h"
#include "entity/xLine.h"

xActionDrawRegCircle::xActionDrawRegCircle(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawRegCircle)
{
}

xActionDrawRegCircle::~xActionDrawRegCircle()
{
	if (!isFinished())
		cancel();
}

void xActionDrawRegCircle::mousePressEvent(QMouseEvent *e)
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
				m_circle->setCircle(mp1, mp2, viewMapToScene(e), 30);
				m_circle->setStyle(xDef::S_RegDrawn);
				// TEST
				m_circle->setSubCircle(m_circle->center(), m_circle->radius());

				// ������ɣ�����ΪS_ActionFinished
				m_status = xDef::AS_ActionFinished;
				e->accept();
			}
			break;

		default:
			break;
		}
	}
}

void xActionDrawRegCircle::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		// ��������ʱ��ʾΪ��ֱ��
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
		// ����������ʱɾ����ʱ��ֱ��
		if (m_line)
		{
			m_scene->removeItem(m_line);
			delete m_line;
			m_line = nullptr;
		}
		if (m_circle == nullptr)
		{
			m_circle = new xRegCircle(m_view);
			m_circle->setStyle(xDef::S_RegDrawing);
			m_scene->addItem(m_circle);
		}
		m_circle->setCircle(xCircleData(mp1, mp2, viewMapToScene(e)), 30);
		e->accept();
		break;

	default:
		break;
	}
}

void xActionDrawRegCircle::mouseReleaseEvent(QMouseEvent *e)
{
}

void xActionDrawRegCircle::cancel()
{
	if (m_line)
	{
		m_scene->removeItem(m_line);
		delete m_line;
		m_line = nullptr;
	}
	if (m_circle)
	{
		m_scene->removeItem(m_circle);
		delete m_circle;
		m_circle = nullptr;
	}
	m_status = xDef::AS_Default;
}
