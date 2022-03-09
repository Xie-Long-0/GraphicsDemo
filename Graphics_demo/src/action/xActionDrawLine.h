#pragma once

#include "action/xActionInterface.h"
#include <QPoint>

class xLine;

class xActionDrawLine : public xActionInterface
{
	Q_OBJECT

public:
	xActionDrawLine(QGraphicsScene *scene, xGraphicView *view, QObject *parent);
	~xActionDrawLine();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

private:
	QPointF p1, p2;
	xLine *tempLine = nullptr;
	bool m_moveP1 = false;
	bool m_moveP2 = false;
};
