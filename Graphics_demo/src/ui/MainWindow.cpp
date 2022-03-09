#include "MainWindow.h"
#include "engine/xGraphicView.h"
#include <QGraphicsScene>
#include <QDebug>

#include "ui/FunctionsTabWidget.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.view_widget->installEventFilter(this);

	m_scene = new QGraphicsScene(this);
	m_view = new xGraphicView(m_scene, ui.view_widget);
	m_view->setObjectName("m_view");
	
	auto tabWidget = new FunctionsTabWidget(m_view, ui.func_tab_widget);

	auto hLayout1 = new QHBoxLayout(ui.view_widget);
	hLayout1->setContentsMargins(0, 0, 0, 0);
	hLayout1->setSpacing(0);
	hLayout1->addWidget(m_view);

	auto hLayout2 = new QHBoxLayout(ui.func_tab_widget);
	hLayout2->setContentsMargins(0, 0, 0, 0);
	hLayout2->setSpacing(0);
	hLayout2->addWidget(tabWidget);

	connect(ui.action_quit, &QAction::triggered, this, &QWidget::close);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui.view_widget)
	{
		if (e->type() == QEvent::Resize)
		{
			m_scene->setSceneRect(ui.view_widget->rect());
			QImage img(ui.view_widget->rect().size(), QImage::Format_RGB888);
			img.fill(Qt::black);
			m_view->setImage(img);
			return true;
		}
		return false;
	}
	else
	{
		return QMainWindow::eventFilter(obj, e);
	}
}
