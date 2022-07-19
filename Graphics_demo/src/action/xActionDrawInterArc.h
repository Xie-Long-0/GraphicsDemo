#pragma once

#include "xActionPreviewInterface.h"

class xInterArc;

class xActionDrawInterArc : public xActionPreviewInterface
{
public:
	xActionDrawInterArc(xGraphicView *view);
	~xActionDrawInterArc();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;
	void calculate() override;

private:
	xInterArc *m_ientity = nullptr;
};
