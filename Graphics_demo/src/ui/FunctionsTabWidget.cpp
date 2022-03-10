#include "FunctionsTabWidget.h"
#include "engine/xGraphicView.h"
#include "action/xActionDrawLine.h"
#include "action/xActionDrawCircle.h"

FunctionsTabWidget::FunctionsTabWidget(xGraphicView *view, QWidget *parent)
	: QWidget(parent)
	, m_view(view)
{
	ui.setupUi(this);

	connect(ui.lineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::onLineBtnClicked);
	connect(ui.circleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::onCircleBtnClicked);
}

FunctionsTabWidget::~FunctionsTabWidget()
{
}

void FunctionsTabWidget::onLineBtnClicked()
{
	xActionDrawLine *lineAction = new xActionDrawLine(m_view, this);
	m_view->setCurrentAction(lineAction);
}

void FunctionsTabWidget::onCircleBtnClicked()
{
	xActionDrawCircle *circleAction = new xActionDrawCircle(m_view, this);
	m_view->setCurrentAction(circleAction);
}
