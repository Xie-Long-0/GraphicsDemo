#pragma once

#include "xActionInterface.h"
#include <QPoint>

class xCircle;
class xLine;

class xActionDrawCircle : public xActionInterface
{
	Q_OBJECT

public:
	xActionDrawCircle(xGraphicView *view, QObject *parent);
	~xActionDrawCircle();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

private:
	QPointF p1, p2;
	xCircle *m_circle = nullptr;
	xLine *m_line = nullptr;
};
