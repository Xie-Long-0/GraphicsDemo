#include "MainWindow.h"
#include "engine/xGraphicView.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <QThread>

#include "FunctionsTabWidget.h"
#include "OperationWidget.h"
#include "RecognizeHandler.h"

#include "xActionDrawLine.h"
#include "xActionDrawCircle.h"
#include "xActionDrawArc.h"
#include "xActionDrawRegLine.h"
#include "xActionDrawRegCircle.h"
#include "xActionDrawRegArc.h"
#include "xActionDrawRegRect.h"
#include "xActionDrawInterCircle.h"
#include "xActionDrawInterArc.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.view_widget->installEventFilter(this);

	m_scene = new QGraphicsScene();
	m_view = new xGraphicView(m_scene, ui.view_widget);

	QImage img(2048, 2048, QImage::Format_RGB888);
	img.fill(Qt::black);
	m_view->setImage(img);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, m_view, [=]() { m_view->setImage(img); });
	timer->start(500);

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
	connect(tabWidget, &FunctionsTabWidget::drawArcEmit, this, &MainWindow::onDrawArc);

	connect(tabWidget, &FunctionsTabWidget::drawRegLineEmit, this, &MainWindow::onDrawRegLine);
	connect(tabWidget, &FunctionsTabWidget::drawRegCircleEmit, this, &MainWindow::onDrawRegCircle);
	connect(tabWidget, &FunctionsTabWidget::drawRegArcEmit, this, &MainWindow::onDrawRegArc);
	connect(tabWidget, &FunctionsTabWidget::drawRegRectEmit, this, &MainWindow::onDrawRegRect);

	connect(tabWidget, &FunctionsTabWidget::drawInterCircle, this, &MainWindow::onDrawInterCircle);
	connect(tabWidget, &FunctionsTabWidget::drawInterArc, this, &MainWindow::onDrawInterArc);

	connect(ui.action_quit, &QAction::triggered, this, &QWidget::close);
	connect(ui.action_delete, &QAction::triggered, m_view, &xGraphicView::removeSelectedItems);
	connect(ui.deleteAllBtn, &QPushButton::clicked, m_view, &xGraphicView::removeAllItems);
}

MainWindow::~MainWindow()
{
	// 将scene的销毁推迟到view窗口销毁之后
	m_scene->deleteLater();
}

void MainWindow::onDrawLine()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawLine(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawLine(m_view);
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

	auto action = new xActionDrawCircle(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawCircle(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawArc()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawArc(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawArc(m_view);
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

	auto action = new xActionDrawRegLine(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawRegLine(m_view);
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

	auto action = new xActionDrawRegCircle(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawRegCircle(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawRegArc()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawRegArc(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawRegArc(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawRegRect()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawRegRect(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawRegRect(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawInterCircle()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawInterCircle(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::calcEmit, this, [=] {
		if (auto action = m_view->getAction(); action != nullptr)
			action->calculate();
		});
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawInterCircle(m_view);
		m_view->setAction(action);
		});
}

void MainWindow::onDrawInterArc()
{
	// 切换操作窗口
	auto opw = new OperationWidget(ui.r_pop_widget);
	m_vLayout->addWidget(opw);
	ui.r_main_widget->hide();
	ui.r_pop_widget->show();

	auto action = new xActionDrawInterArc(m_view);
	m_view->setAction(action);

	// 连接确定、取消、下一步信号槽
	connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
	connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
	connect(opw, &OperationWidget::calcEmit, this, [=] {
		if (auto action = m_view->getAction(); action != nullptr)
			action->calculate();
		});
	connect(opw, &OperationWidget::nextEmit, this, [=] {
		m_view->finishAction();
		auto action = new xActionDrawInterArc(m_view);
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
