#pragma once

#include <QWidget>
#include "ui_FunctionsTabWidget.h"

class xGraphicView;

class FunctionsTabWidget : public QWidget
{
	Q_OBJECT

public:
	FunctionsTabWidget(xGraphicView *view, QWidget *parent);
	~FunctionsTabWidget();

public slots:
	void onLineBtnClicked();
	void onCircleBtnClicked();

private:
	Ui::FunctionsTabWidget ui;

	xGraphicView *m_view = nullptr;
};
