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
	void drawArcEmit();

	void drawRegLineEmit();
	void drawRegCircleEmit();
	void drawRegArcEmit();
	void drawRegRectEmit();

	void drawInterCircle();
	void drawInterArc();

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	Ui::FunctionsTabWidget ui;
};
