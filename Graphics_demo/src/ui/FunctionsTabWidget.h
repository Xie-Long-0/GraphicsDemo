#pragma once

#include <QWidget>
#include "ui_FunctionsTabWidget.h"

class FunctionsTabWidget : public QWidget
{
	Q_OBJECT

public:
	FunctionsTabWidget(QWidget *parent);
	~FunctionsTabWidget();

public slots:

signals:
	void drawLineEmit();
	void drawCircleEmit();

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	Ui::FunctionsTabWidget ui;
};
