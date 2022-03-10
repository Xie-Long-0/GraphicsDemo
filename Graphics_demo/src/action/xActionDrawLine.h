#pragma once

#include "xActionInterface.h"
#include <QPoint>

class xLine;

class xActionDrawLine : public xActionInterface
{
	Q_OBJECT

public:
	xActionDrawLine(xGraphicView *view, QObject *parent);
	~xActionDrawLine();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

private:
	QPointF mp;
	xLine *m_line = nullptr;
	bool m_moveP1 = false;
	bool m_moveP2 = false;
};
