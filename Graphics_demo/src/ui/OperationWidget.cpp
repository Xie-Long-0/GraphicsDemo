#include "OperationWidget.h"
#include <QPainter>
#include <QStyleOption>

OperationWidget::OperationWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	
	connect(ui.confirmBtn, &QPushButton::clicked, this, &OperationWidget::confirmEmit);
	connect(ui.cancelBtn, &QPushButton::clicked, this, &OperationWidget::cancelEmit);
	connect(ui.calcBtn, &QPushButton::clicked, this, &OperationWidget::calcEmit);
	connect(ui.nextBtn, &QPushButton::clicked, this, &OperationWidget::nextEmit);
}

void OperationWidget::setActionName(const QString &name)
{
	ui.label->setText(name);
}

void OperationWidget::setCalcEnabled(bool enabled)
{
	ui.calcBtn->setEnabled(enabled);
	ui.calcBtn->setVisible(enabled);
}

void OperationWidget::setNextEnabled(bool enabled)
{
	ui.nextBtn->setEnabled(enabled);
	ui.nextBtn->setVisible(enabled);
}

void OperationWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	QStyleOption op;
	op.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}
