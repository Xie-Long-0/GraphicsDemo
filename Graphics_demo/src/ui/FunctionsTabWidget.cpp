#include "FunctionsTabWidget.h"
#include <QPainter>
#include <QStyleOption>

FunctionsTabWidget::FunctionsTabWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.lineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawLineEmit);
	connect(ui.circleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawCircleEmit);

	connect(ui.regLineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegLineEmit);
	connect(ui.regCircleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegCircleEmit);
}

FunctionsTabWidget::~FunctionsTabWidget()
{
}

void FunctionsTabWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	QStyleOption op;
	op.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}
