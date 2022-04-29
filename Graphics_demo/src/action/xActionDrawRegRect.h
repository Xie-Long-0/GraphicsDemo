#pragma once

#include "xActionPreviewInterface.h"

class xActionDrawRegRect : public xActionPreviewInterface
{
public:
	xActionDrawRegRect(xGraphicView *view);
	~xActionDrawRegRect();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;

};
