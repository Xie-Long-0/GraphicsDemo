#include "xActionDrawInterArc.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>

#include "xGraphicView.h"
#include "xInterArc.h"
#include "xArc.h"
#include "xRegArc.h"

xActionDrawInterArc::xActionDrawInterArc(xGraphicView *view)
	: xActionPreviewInterface(view, xDef::AT_DrawInterArc)
{
}

xActionDrawInterArc::~xActionDrawInterArc()
{
	if (!isFinished())
		cancel();
}

void xActionDrawInterArc::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		switch (m_status)
		{
		case xDef::AS_Default:
		{
			auto gi = m_view->itemAt(e->pos());
			if (gi == nullptr || (gi->type() != xArc::Type && gi->type() != xRegArc::Type))
				return;

			xEntity *item = static_cast<xEntity *>(gi);
			if (auto pe = item->parentEntity(); pe != nullptr)
				item = pe;

			if (m_ientity == nullptr)
			{
				m_ientity = new xInterArc(m_view);
			}
			// °ó¶¨Ô²
			m_ientity->bindEntity(item);
			m_ientity->setText("Bind Arc");
			m_ientity->setAnchorPoint(viewMapToScene(e));
			m_ientity->setStyle(xDef::S_TxtDrawing);
			m_scene->addItem(m_ientity);
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

void xActionDrawInterArc::mouseMoveEvent(QMouseEvent *e)
{
	switch (m_status)
	{
	case xDef::AS_DrawEntity1_P1:
		if (m_ientity)
		{
			m_ientity->setAnchorPoint(viewMapToScene(e));
		}
		break;
	default:
		break;
	}
}

void xActionDrawInterArc::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (m_status == xDef::AS_Measured && m_ientity)
		{
			m_ientity->calculate();
			m_status = xDef::AS_ActionFinished;
			e->accept();
		}
	}
}

void xActionDrawInterArc::cancel()
{
	if (m_ientity)
	{
		m_scene->removeItem(m_ientity);
		m_ientity->deleteLater();
		m_ientity = nullptr;
	}
	m_status = xDef::AS_Default;
}

void xActionDrawInterArc::calculate()
{
	if (m_ientity)
		m_ientity->calculate();
}
