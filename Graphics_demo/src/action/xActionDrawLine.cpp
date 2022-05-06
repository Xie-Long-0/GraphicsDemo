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
	if (!isFinished())
		cancel();
}

void xActionDrawLine::mousePressEvent(QMouseEvent *e)
{
	auto spos = viewMapToScene(e);
	if (e->button() == Qt::LeftButton)
	{
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
				m_line->setLine(mp, spos);
				m_line->setStyle(xDef::S_Drawn);
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

void xActionDrawLine::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		if (Distance(mp, viewMapToScene(e)) > DELTA_DIST_2)
		{
			if (m_line == nullptr)
			{
				m_line = new xLine(m_view);
				m_line->setStyle(xDef::S_Drawing);
				m_scene->addItem(m_line);
			}
			m_line->setLine(mp, viewMapToScene(e));
			e->accept();
		}
		break;

	default:
		break;
	}
}

void xActionDrawLine::mouseReleaseEvent(QMouseEvent *e)
{
}

void xActionDrawLine::cancel()
{
	if (m_line)
	{
		m_scene->removeItem(m_line);
		delete m_line;
		m_line = nullptr;
	}
	m_status = xDef::AS_Default;
}
