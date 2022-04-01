#include "xGraphicView.h"
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
#include "action/xActionPreviewInterface.h"
#include "action/xActionDefault.h"
#include "entity/xEntity.h"

xGraphicView::xGraphicView(QGraphicsScene *scene, QWidget *parent)
	: QGraphicsView(scene, parent)
{
	setMouseTracking(true);
	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	// 隐藏水平滚动条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		// 隐藏垂直滚动条
	
	// 添加背景图片实体，并禁止选中和移动
	m_pixmap = new QGraphicsPixmapItem();
	m_pixmap->setAcceptHoverEvents(false);
	m_pixmap->setAcceptTouchEvents(false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsFocusable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsMovable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsSelectable, false);

	QImage img(2048, 2048, QImage::Format_RGB888);
	img.fill(Qt::black);
	m_pixmap->setPixmap(QPixmap::fromImage(img));

	scene->addItem(m_pixmap);

	m_default = new xActionDefault(this);
}

xGraphicView::~xGraphicView()
{
	if (m_action)
		delete m_action;
	if (m_default)
		delete m_default;
}

void xGraphicView::setAction(xActionPreviewInterface *action)
{
	if (m_action)
	{
		delete m_action;
	}
	m_action = action;
}

void xGraphicView::finishAction()
{
	if (m_action)
	{
		if (!m_action->isFinished())
			m_action->cancel();
		delete m_action;
		m_action = nullptr;
	}
}

void xGraphicView::cancelAction()
{
	if (m_action)
	{
		m_action->cancel();
		delete m_action;
		m_action = nullptr;
	}
}

void xGraphicView::setPixmap(const QPixmap &pixmap)
{
	m_pixmap->setPixmap(pixmap);
}

void xGraphicView::setImage(const QImage &image)
{
	m_pixmap->setPixmap(QPixmap::fromImage(image));
}

void xGraphicView::zoomIn()
{
}

void xGraphicView::zoomOut()
{
}

void xGraphicView::zoomByFactor(qreal factor)
{
}

void xGraphicView::mousePressEvent(QMouseEvent *e)
{
	e->ignore();
	if (m_action && !m_action->isFinished())
	{
		m_action->mousePressEvent(e);
	}
	else
	{
		m_default->mousePressEvent(e);
	}
	if (e->isAccepted())
		return;
	QGraphicsView::mousePressEvent(e);
}

void xGraphicView::mouseMoveEvent(QMouseEvent *e)
{
	e->ignore();
	if (m_action && !m_action->isFinished())
	{
		m_action->mouseMoveEvent(e);
	}
	else
	{
		m_default->mouseMoveEvent(e);
	}
	if (e->isAccepted())
		return;
	QGraphicsView::mouseMoveEvent(e);
}

void xGraphicView::mouseReleaseEvent(QMouseEvent *e)
{
	e->ignore();
	if (m_action && !m_action->isFinished())
	{
		m_action->mouseReleaseEvent(e);
	}
	else
	{
		m_default->mouseReleaseEvent(e);
	}
	if (e->isAccepted())
		return;
	QGraphicsView::mouseReleaseEvent(e);
}

void xGraphicView::wheelEvent(QWheelEvent *e)
{
	auto delta = e->angleDelta().y();
	// Pressed Ctrl key
	if (e->modifiers() & Qt::ControlModifier)
	{
		if (delta > 0)
		{
		}
		else if (delta < 0)
		{
		}
	}
	// Pressed Shift key
	else if (e->modifiers() & Qt::ShiftModifier)
	{
		if (delta > 0)
		{
		}
		else if (delta < 0)
		{
		}
	}
	else if (delta > 0)
	{
		scale(1.25, 1.25);
	}
	else if (delta < 0)
	{
		scale(0.8, 0.8);
	}
	else
	{
		QGraphicsView::wheelEvent(e);
	}
}

void xGraphicView::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Up:
		translate(0, -10);
		break;
	case Qt::Key_Down:
		translate(0, 10);
		break;
	case Qt::Key_Left:
		translate(-10, 0);
		break;
	case Qt::Key_Right:
		translate(10, 0);
		break;
	default:
		QGraphicsView::keyPressEvent(e);
		break;
	}
}

void xGraphicView::mouseDoubleClickEvent(QMouseEvent *e)
{
	finishAction();
}
