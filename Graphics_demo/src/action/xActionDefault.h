#pragma once

#include "xActionInterface.h"

class xActionDefault : public xActionInterface
{
public:
	xActionDefault(xGraphicView *view);
	~xActionDefault();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
};
