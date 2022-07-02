#pragma once

#include <QWidget>
#include "ui_OperationWidget.h"

class OperationWidget : public QWidget
{
	Q_OBJECT

public:
	OperationWidget(QWidget *parent = nullptr);

signals:
	void confirmEmit();
	void cancelEmit();
	void calcEmit();
	void nextEmit();

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	Ui::OperationWidget ui;
};
