#pragma once

#include "xActionPreviewInterface.h"
#include <QPoint>

class xArc;
class xLine;

class xActionDrawArc : public xActionPreviewInterface
{
public:
	xActionDrawArc(xGraphicView *view);
	~xActionDrawArc();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void cancel() override;

private:
	QPointF mp1, mp2;
	xArc *m_arc = nullptr;
	xLine *m_line = nullptr;
};
