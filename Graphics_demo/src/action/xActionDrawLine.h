#pragma once

#include "xActionPreviewInterface.h"
#include <QPoint>

class xRegLine;

class xActionDrawLine : public xActionPreviewInterface
{
public:
	xActionDrawLine(xGraphicView *view);
	~xActionDrawLine();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;

private:
	QPointF mp;
	xRegLine *m_line = nullptr;
};
