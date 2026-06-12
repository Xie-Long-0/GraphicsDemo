#pragma once

#include <QWidget>
#include <QString>
#include "ui_OperationWidget.h"

class OperationWidget : public QWidget
{
	Q_OBJECT

public:
	OperationWidget(QWidget *parent = nullptr);

	void setActionName(const QString &name);
	void setCalcEnabled(bool enabled);
	void setNextEnabled(bool enabled);

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
