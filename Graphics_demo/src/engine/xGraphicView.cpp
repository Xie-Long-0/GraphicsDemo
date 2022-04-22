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
	setFrameShape(QFrame::NoFrame);
	setMouseTracking(true);
	setRenderHint(QPainter::Antialiasing);
	
	// ��ӱ���ͼƬʵ�壬����ֹѡ�к��ƶ�
	m_pixmap = new QGraphicsPixmapItem();
	m_pixmap->setAcceptHoverEvents(false);
	m_pixmap->setAcceptTouchEvents(false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsFocusable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsMovable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsSelectable, false);
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
		if (m_action->isFinished())
			m_action->confirm();
		else
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
	if (sceneRect().size() != pixmap.size())
	{
		setSceneRect(pixmap.rect());
		const qreal fw = width() / scene()->width();
		const qreal fh = height() / scene()->height();
		m_initFactor = std::max(fw, fh);
	}
	m_pixmap->setPixmap(pixmap);
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

void xGraphicView::resizeScene()
{
	const qreal fw = width() / scene()->width();
	const qreal fh = height() / scene()->height();
	m_initFactor = std::max(fw, fh);
	scale(m_initFactor, m_initFactor);
	
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	// ����ˮƽ������
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		// ���ش�ֱ������
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
	// ȥ��Ctrl���μ��Ķ�ѡ����
	if (e->modifiers() & Qt::ControlModifier)
		e->setModifiers(e->modifiers() & ~Qt::ControlModifier);
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
	// ȥ��Ctrl���μ��Ķ�ѡ����
	if (e->modifiers() & Qt::ControlModifier)
		e->setModifiers(e->modifiers() & ~Qt::ControlModifier);
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
		onScaleChanged();
	}
	else if (delta < 0)
	{
		scale(0.8, 0.8);
		onScaleChanged();
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
	e->accept();
}

void xGraphicView::onScaleChanged()
{
	if (scaleFactor() <= m_initFactor)
	{
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	// ����ˮƽ������
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		// ���ش�ֱ������
	}
	else
	{
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	}
}
