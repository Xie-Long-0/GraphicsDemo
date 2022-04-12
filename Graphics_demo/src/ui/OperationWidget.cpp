#include "OperationWidget.h"
#include <QPainter>
#include <QStyleOption>

OperationWidget::OperationWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	
	connect(ui.confirmBtn, &QPushButton::clicked, this, [=] {
		emit confirmEmit();
		close();
		});
	connect(ui.cancelBtn, &QPushButton::clicked, this, [=] {
		emit cancelEmit();
		close();
		});
	connect(ui.nextBtn, &QPushButton::clicked, this, &OperationWidget::nextEmit);
}

void OperationWidget::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	QStyleOption op;
	op.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &op, &p, this);
}
