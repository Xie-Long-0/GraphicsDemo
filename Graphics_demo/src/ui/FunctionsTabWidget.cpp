#include "FunctionsTabWidget.h"
#include "engine/xGraphicView.h"
#include "action/xActionDrawLine.h"

FunctionsTabWidget::FunctionsTabWidget(xGraphicView *view, QWidget *parent)
	: QWidget(parent)
	, m_view(view)
{
	ui.setupUi(this);

	connect(ui.lineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::onLineBtnClicked);
}

FunctionsTabWidget::~FunctionsTabWidget()
{
}

void FunctionsTabWidget::onLineBtnClicked()
{
	xActionDrawLine *lineAction = new xActionDrawLine(m_view->scene(), m_view, this);
	m_view->setCurrentAction(lineAction);
}
