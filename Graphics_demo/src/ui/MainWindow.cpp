#include "MainWindow.h"
#include "engine/xGraphicView.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

#include "FunctionsTabWidget.h"
#include "OperationWidget.h"

#include "xActionDrawLine.h"
#include "xActionDrawCircle.h"
#include "xActionDrawRegLine.h"
#include "xActionDrawRegCircle.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.view_widget->installEventFilter(this);

	m_scene = new QGraphicsScene(this);
	m_view = new xGraphicView(m_scene, ui.view_widget);

	QImage img(2048, 2048, QImage::Format_RGB888);
	img.fill(Qt::black);
	m_view->setImage(img);

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

	connect(tabWidget, &FunctionsTabWidget::drawRegLineEmit, this, &MainWindow::onDrawRegLine);
	connect(tabWidget, &FunctionsTabWidget::drawRegCircleEmit, this, &MainWindow::onDrawRegCircle);

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

	xActionDrawLine *action = new xActionDrawLine(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawLine *action = new xActionDrawLine(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawCircle()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	xActionDrawCircle *action = new xActionDrawCircle(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawCircle *action = new xActionDrawCircle(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawRegLine()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	xActionDrawRegLine *action = new xActionDrawRegLine(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawRegLine *action = new xActionDrawRegLine(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawRegCircle()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	xActionDrawRegCircle *action = new xActionDrawRegCircle(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		xActionDrawRegCircle *action = new xActionDrawRegCircle(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	QStyleOption op;
	op.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui.view_widget)
	{
		if (e->type() == QEvent::Resize)
		{
			if (m_firstResize)
			{
				m_view->resizeScene();
				m_firstResize = false;
			}
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
