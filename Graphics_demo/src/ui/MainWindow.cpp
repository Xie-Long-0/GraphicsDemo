#include "engine/xGraphicView.h"
#include "MainWindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QThread>
#include <QTimer>
#include <functional>

#include "FunctionsTabWidget.h"
#include "OperationWidget.h"
#include "RecognizeHandler.h"

#include "xActionDrawArc.h"
#include "xActionDrawCircle.h"
#include "xActionDrawInterArc.h"
#include "xActionDrawInterCircle.h"
#include "xActionDrawLine.h"
#include "xActionDrawRegArc.h"
#include "xActionDrawRegCircle.h"
#include "xActionDrawRegLine.h"
#include "xActionDrawRegRect.h"

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

void MainWindow::startAction(const std::function<xActionPreviewInterface *()> &factory, bool enableCalc)
{
    auto opw = new OperationWidget(ui.r_pop_widget);
    m_vLayout->addWidget(opw);
    ui.r_main_widget->hide();
    ui.r_pop_widget->show();

    m_view->setAction(factory());

    connect(opw, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
    connect(opw, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
    if (enableCalc)
    {
        connect(opw, &OperationWidget::calcEmit, this, [=] {
            if (auto action = m_view->getAction(); action != nullptr)
                action->calculate();
        });
    }
    connect(opw, &OperationWidget::nextEmit, this, [=] {
        m_view->finishAction();
        m_view->setAction(factory());
    });
}

void MainWindow::onDrawLine()
{
    startAction([=] { return new xActionDrawLine(m_view); }, false);
}
void MainWindow::onDrawCircle()
{
    startAction([=] { return new xActionDrawCircle(m_view); }, false);
}
void MainWindow::onDrawArc()
{
    startAction([=] { return new xActionDrawArc(m_view); }, false);
}
void MainWindow::onDrawRegLine()
{
    startAction([=] { return new xActionDrawRegLine(m_view); }, false);
}
void MainWindow::onDrawRegCircle()
{
    startAction([=] { return new xActionDrawRegCircle(m_view); }, false);
}
void MainWindow::onDrawRegArc()
{
    startAction([=] { return new xActionDrawRegArc(m_view); }, false);
}
void MainWindow::onDrawRegRect()
{
    startAction([=] { return new xActionDrawRegRect(m_view); }, false);
}
void MainWindow::onDrawInterCircle()
{
    startAction([=] { return new xActionDrawInterCircle(m_view); }, true);
}
void MainWindow::onDrawInterArc()
{
    startAction([=] { return new xActionDrawInterArc(m_view); }, true);
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
