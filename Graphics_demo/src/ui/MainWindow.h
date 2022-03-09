#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class xGraphicView;
class QGraphicsScene;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

public slots:

protected:
	bool eventFilter(QObject *obj, QEvent *e) override;

private:
	Ui::MainWindow ui;
	xGraphicView *m_view = nullptr;
	QGraphicsScene *m_scene = nullptr;
};
