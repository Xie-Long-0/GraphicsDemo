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
			if (Distance(mp, spos) > DELTA_DIST_2)
			{
				m_line->setLine(mp, spos);
				m_line->setStyle(xStyle::Drawn);
				// 操作完成，设置为S_ActionFinished
				m_status = xDef::S_ActionFinished;
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
	auto spos = pointMapToScene(e);
	switch (m_status)
	{
	case xDef::S_DrawEntity1_P1:
		if (Distance(mp, spos) > DELTA_DIST_2)
		{
			if (m_line == nullptr)
			{
				m_line = new xLine(m_view);
				m_line->setStyle(xStyle::Drawing);
				m_scene->addItem(m_line);
			}
			m_line->setLine(mp, pointMapToScene(e));
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
	m_status = xDef::S_Default;
}
