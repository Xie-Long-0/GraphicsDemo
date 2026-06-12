#include "engine/xGraphicView.h"
#include "MainWindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QString>
#include <QThread>
#include <QTimer>
#include <functional>
#include <memory>
#include <utility>

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

void MainWindow::startAction(ActionDescriptor descriptor)
{
    if (!descriptor.factory)
        return;

    destroyOperationWidget();

    m_operationWidget = new OperationWidget(ui.r_pop_widget);
    m_operationWidget->setActionName(QString::fromUtf8(descriptor.name));
    m_operationWidget->setCalcEnabled(descriptor.enableCalc);
    m_operationWidget->setNextEnabled(descriptor.enableNext);
    m_vLayout->addWidget(m_operationWidget);
    ui.r_main_widget->hide();
    ui.r_pop_widget->show();

    m_view->setAction(descriptor.factory());

    auto operationWidget = m_operationWidget;
    connect(operationWidget, &QObject::destroyed, this, [this, operationWidget] {
        if (m_operationWidget == operationWidget)
            m_operationWidget = nullptr;
    });
    connect(m_operationWidget, &OperationWidget::confirmEmit, this, &MainWindow::onOperateFinished);
    connect(m_operationWidget, &OperationWidget::cancelEmit, this, &MainWindow::onOperateCanceled);
    if (descriptor.enableCalc)
    {
        connect(m_operationWidget, &OperationWidget::calcEmit, this, [this] {
            if (auto action = m_view->getAction(); action != nullptr)
                action->calculate();
        });
    }
    if (descriptor.enableNext)
    {
        connect(m_operationWidget, &OperationWidget::nextEmit, this, [this, descriptor = std::move(descriptor)] {
            m_view->finishAction();
            m_view->setAction(descriptor.factory());
        });
    }
}

void MainWindow::destroyOperationWidget()
{
    if (m_operationWidget == nullptr)
        return;

    m_vLayout->removeWidget(m_operationWidget);
    m_operationWidget->deleteLater();
    m_operationWidget = nullptr;
}

void MainWindow::onDrawLine()
{
    startAction({ "直线", [this] { return std::make_unique<xActionDrawLine>(m_view); } });
}
void MainWindow::onDrawCircle()
{
    startAction({ "圆", [this] { return std::make_unique<xActionDrawCircle>(m_view); } });
}
void MainWindow::onDrawArc()
{
    startAction({ "圆弧", [this] { return std::make_unique<xActionDrawArc>(m_view); } });
}
void MainWindow::onDrawRegLine()
{
    startAction({ "线型区域", [this] { return std::make_unique<xActionDrawRegLine>(m_view); } });
}
void MainWindow::onDrawRegCircle()
{
    startAction({ "圆形区域", [this] { return std::make_unique<xActionDrawRegCircle>(m_view); } });
}
void MainWindow::onDrawRegArc()
{
    startAction({ "圆弧区域", [this] { return std::make_unique<xActionDrawRegArc>(m_view); } });
}
void MainWindow::onDrawRegRect()
{
    startAction({ "矩形区域", [this] { return std::make_unique<xActionDrawRegRect>(m_view); } });
}
void MainWindow::onDrawInterCircle()
{
    startAction({ "拟合圆", [this] { return std::make_unique<xActionDrawInterCircle>(m_view); }, true });
}
void MainWindow::onDrawInterArc()
{
    startAction({ "拟合圆弧", [this] { return std::make_unique<xActionDrawInterArc>(m_view); }, true });
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
    destroyOperationWidget();
    ui.r_pop_widget->hide();
    ui.r_main_widget->show();
}

void MainWindow::onOperateCanceled()
{
    m_view->cancelAction();
    destroyOperationWidget();
    ui.r_pop_widget->hide();
    ui.r_main_widget->show();
}
