#pragma once

#include "xActionPreviewInterface.h"

class xInterCircle;

class xActionDrawInterCircle : public xActionPreviewInterface
{
public:
	xActionDrawInterCircle(xGraphicView *view);
	~xActionDrawInterCircle();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;
	void calculate() override;

private:
	xInterCircle *m_icircle = nullptr;
};
