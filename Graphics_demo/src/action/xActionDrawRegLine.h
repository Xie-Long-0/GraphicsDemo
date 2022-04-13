#pragma once

#include "xActionPreviewInterface.h"
#include <QPoint>

class xRegLine;

class xActionDrawRegLine : public xActionPreviewInterface
{
public:
	xActionDrawRegLine(xGraphicView *view);
	~xActionDrawRegLine();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;

private:
	QPointF mp;
	xRegLine *m_line = nullptr;
};
