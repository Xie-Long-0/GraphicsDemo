#pragma once

#include "xActionPreviewInterface.h"
#include <QPoint>

class xLine;

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
	xLine *m_line = nullptr;
	bool m_moveP1 = false;
	bool m_moveP2 = false;
};
