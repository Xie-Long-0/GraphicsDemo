#pragma once

#include "action/xActionInterface.h"

class xActionDefault : public xActionInterface
{
	Q_OBJECT

public:
	xActionDefault(QGraphicsScene *scene, xGraphicView *view, QObject *parent);
	~xActionDefault();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

};
