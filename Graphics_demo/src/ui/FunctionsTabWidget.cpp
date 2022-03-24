#include "FunctionsTabWidget.h"
#include <QPainter>
#include <QStyleOption>

FunctionsTabWidget::FunctionsTabWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.lineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawLineEmit);
	connect(ui.circleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawCircleEmit);
}

FunctionsTabWidget::~FunctionsTabWidget()
{
}

void FunctionsTabWidget::paintEvent(QPaintEvent *e)
{
	QStyleOption op;
	op.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}