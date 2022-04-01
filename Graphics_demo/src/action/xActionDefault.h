#pragma once

#include "xActionInterface.h"

class xEntity;

class xActionDefault : public xActionInterface
{
public:
	xActionDefault(xGraphicView *view);
	~xActionDefault();

	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

private:
	QPointF m_p;
	xEntity *m_item = nullptr;
	bool m_willMoveItem = false;
	bool m_isGrabCtrlPoint = false;
	bool m_isGrabRegionEdge = false;
};
