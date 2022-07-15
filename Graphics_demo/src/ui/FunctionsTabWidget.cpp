#include "FunctionsTabWidget.h"
#include <QPainter>
#include <QStyleOption>

FunctionsTabWidget::FunctionsTabWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.lineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawLineEmit);
	connect(ui.circleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawCircleEmit);
	connect(ui.arcBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawArcEmit);

	connect(ui.regLineBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegLineEmit);
	connect(ui.regCircleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegCircleEmit);
	connect(ui.regArcBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegArcEmit);
	connect(ui.regRectBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawRegRectEmit);

	connect(ui.interCircleBtn, &QPushButton::clicked, this, &FunctionsTabWidget::drawInterCircle);
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
