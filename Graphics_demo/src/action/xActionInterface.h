#pragma once

#include "engine/xTypeDef.h"

class QGraphicsScene;
class QMouseEvent;
class xGraphicView;

/**
 * @brief Action类的接口类，用于各种绘图动作
*/
class xActionInterface
{
public:
	xActionInterface(xGraphicView *view, xDef::ActionType type);
	virtual ~xActionInterface();

	xDef::ActionType type() const noexcept { return m_type; }
	xDef::ActionStatus status() const noexcept { return m_status; }

	virtual void mousePressEvent(QMouseEvent *e) = 0;
	virtual void mouseMoveEvent(QMouseEvent *e) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *e) = 0;

protected:
	QPointF viewMapToScene(QMouseEvent *e) const;

	QGraphicsScene *m_scene = nullptr;
	xGraphicView *m_view = nullptr;
	xDef::ActionStatus m_status = xDef::AS_Default;

private:
	xDef::ActionType m_type = xDef::AT_Unknown;
};
