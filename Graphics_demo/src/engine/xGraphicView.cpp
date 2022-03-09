#include "xGraphicView.h"
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
#include "action/xActionDefault.h"

xGraphicView::xGraphicView(QGraphicsScene *scene, QWidget *parent)
	: QGraphicsView(scene, parent)
{
	setMouseTracking(true);
	setRenderHint(QPainter::Antialiasing);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	// 隐藏水平滚动条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		// 隐藏垂直滚动条
	
	m_pixmap = new QGraphicsPixmapItem();
	m_pixmap->setAcceptHoverEvents(false);
	m_pixmap->setAcceptTouchEvents(false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsFocusable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsMovable, false);
	m_pixmap->setFlag(QGraphicsItem::ItemIsSelectable, false);
	scene->addItem(m_pixmap);

	defaultAction = new xActionDefault(scene, this, this);
	currentAction = defaultAction;
}

xGraphicView::~xGraphicView()
{
}

void xGraphicView::setCurrentAction(xActionInterface *action)
{
	if (action != nullptr)
	{
		currentAction = action;
	}
	else
	{
		currentAction = defaultAction;
	}
}

void xGraphicView::finishAction()
{
	if (currentAction != defaultAction)
	{
		currentAction->deleteLater();
		currentAction = defaultAction;
	}
}

void xGraphicView::setPixmap(const QPixmap &pixmap)
{
	m_pixmap->setPixmap(pixmap);
	m_pixmap->update();
}

void xGraphicView::setImage(const QImage &image)
{
	m_pixmap->setPixmap(QPixmap::fromImage(image));
	m_pixmap->update();
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
	currentAction->mousePressEvent(e);
	if (currentAction->isProcessed())
		return;
	return QGraphicsView::mousePressEvent(e);
}

void xGraphicView::mouseMoveEvent(QMouseEvent *e)
{
	currentAction->mouseMoveEvent(e);
	if (currentAction->isProcessed())
		return;
	return QGraphicsView::mouseMoveEvent(e);
}

void xGraphicView::mouseReleaseEvent(QMouseEvent *e)
{
	currentAction->mouseReleaseEvent(e);
	if (currentAction->isProcessed())
		return;
	return QGraphicsView::mouseReleaseEvent(e);
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
		qDebug() << transform();
		scale(1.25, 1.25);
		qDebug() << transform();
	}
	else if (delta < 0)
	{
		qDebug() << transform();
		scale(0.8, 0.8);
		qDebug() << transform();
	}
	else
	{
		QGraphicsView::wheelEvent(e);
	}
	//scene()->update();
	//updateSceneRect(rect());
	//e->accept();
}

void xGraphicView::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Up:
		qDebug() << transform();
		translate(0, -10);
		qDebug() << transform();
		break;
	case Qt::Key_Down:
		qDebug() << transform();
		translate(0, 10);
		qDebug() << transform();
		break;
	case Qt::Key_Left:
		qDebug() << transform();
		translate(-10, 0);
		qDebug() << transform();
		break;
	case Qt::Key_Right:
		qDebug() << transform();
		translate(10, 0);
		qDebug() << transform();
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
