#include "xActionDrawInterCircle.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include <QThread>

#include "engine/xGraphicView.h"
#include "entity/xCircle.h"
#include "entity/xRegCircle.h"
#include "entity/xInterCircle.h"
#include "RecognizeHandler.h"

xActionDrawInterCircle::xActionDrawInterCircle(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawInterCircle)
{
}

xActionDrawInterCircle::~xActionDrawInterCircle()
{
	if (!isFinished())
		cancel();
}

void xActionDrawInterCircle::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		switch (m_status)
		{
		case xDef::AS_Default:
		{
			auto gi = m_view->itemAt(e->pos());
			if (gi == nullptr || (gi->type() != xCircle::Type && gi->type() != xRegCircle::Type))
				return;

			xEntity *item = static_cast<xEntity *>(gi);
			if (auto pe = item->parentEntity(); pe != nullptr)
				item = pe;

			if (m_icircle == nullptr)
			{
				m_icircle = new xInterCircle(m_view);
			}
			// °ó¶¨Ô²
			m_icircle->bindEntity(item);
			m_icircle->setText("Bind Circle");
			m_icircle->setAnchorPoint(viewMapToScene(e));
			m_icircle->setStyle(xDef::S_TxtDrawing);
			m_scene->addItem(m_icircle);
			m_status = xDef::AS_DrawEntity1_P1;
			e->accept();
			break;
		}
		case xDef::AS_DrawEntity1_P1:
			m_status = xDef::AS_Measured;
			e->accept();
			break;
		case xDef::AS_Measured:
			break;
		default:
			break;
		}
	}
}

void xActionDrawInterCircle::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		if (m_icircle)
		{
			m_icircle->setAnchorPoint(viewMapToScene(e));
		}
		break;
	default:
		break;
	}
}

void xActionDrawInterCircle::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_status == xDef::AS_Measured && m_icircle)
		{
			m_icircle->calculate();
			m_status = xDef::AS_ActionFinished;
			e->accept();
		}
	}
}

void xActionDrawInterCircle::cancel()
{
	if (m_icircle)
	{
		m_scene->removeItem(m_icircle);
		delete m_icircle;
		m_icircle = nullptr;
	}
	m_status = xDef::AS_Default;
}

void xActionDrawInterCircle::calculate()
{
	if (m_icircle)
		m_icircle->calculate();
}
