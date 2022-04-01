#include "MainWindow.h"
#include "engine/xGraphicView.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

#include "FunctionsTabWidget.h"
#include "OperationWidget.h"

#include "action/xActionDrawLine.h"
#include "action/xActionDrawCircle.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.view_widget->installEventFilter(this);

	m_scene = new QGraphicsScene(this);
	m_view = new xGraphicView(m_scene, ui.view_widget);
	
	auto hLayout1 = new QHBoxLayout(ui.view_widget);
	hLayout1->setContentsMargins(0, 0, 0, 0);
	hLayout1->setSpacing(0);
	hLayout1->addWidget(m_view);

	auto tabWidget = new FunctionsTabWidget(ui.func_tab_widget);
	auto hLayout2 = new QHBoxLayout(ui.func_tab_widget);
	hLayout2->setContentsMargins(0, 0, 0, 0);
	hLayout2->setSpacing(0);
	hLayout2->addWidget(tabWidget);

	m_vLayout = new QVBoxLayout(ui.r_pop_widget);
	m_vLayout->setContentsMargins(0, 0, 0, 0);
	m_vLayout->setSpacing(0);
	ui.r_pop_widget->hide();

	connect(tabWidget, &FunctionsTabWidget::drawLineEmit, this, &MainWindow::onDrawLine);
	connect(tabWidget, &FunctionsTabWidget::drawCircleEmit, this, &MainWindow::onDrawCircle);

	connect(ui.action_quit, &QAction::triggered, this, &QWidget::close);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onDrawLine()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	xActionDrawLine *lineAction = new xActionDrawLine(m_view);
	m_view->setAction(lineAction);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawLine *lineAction = new xActionDrawLine(m_view);
		m_view->setAction(lineAction);
		});
}

void MainWindow::onDrawCircle()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	xActionDrawCircle *circleAction = new xActionDrawCircle(m_view);
	m_view->setAction(circleAction);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawCircle *circleAction = new xActionDrawCircle(m_view);
		m_view->setAction(circleAction);
		});
}

void MainWindow::paintEvent(QPaintEvent *e)
{
	QStyleOption op;
	op.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui.view_widget)
	{
		if (e->type() == QEvent::Resize)
		{
			// 窗口大小改变时调整视图场景大小
			m_scene->setSceneRect(ui.view_widget->rect());
			return true;
		}
		return false;
	}
	else
	{
		return QMainWindow::eventFilter(obj, e);
	}
}

void MainWindow::onOperateFinished()
{
	m_view->finishAction();
	ui.r_pop_widget->hide();
	ui.r_main_widget->show();
}

void MainWindow::onOperateCanceled()
{
	m_view->cancelAction();
	ui.r_pop_widget->hide();
	ui.r_main_widget->show();
}
