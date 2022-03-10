#pragma once

#include <QObject>
#include "engine/xTypeDef.h"

class QGraphicsScene;
class QMouseEvent;
class xGraphicView;

/**
 * @brief Action类的接口类，用于各种绘图动作
*/
class xActionInterface : public QObject
{
	Q_OBJECT

public:
	xDef::ActionType type() const { return m_type; }
	//xDef::ActionStatus status() const { return m_status; }
	//void setStatus(xDef::ActionStatus s) { m_status = s; }
	bool isProcessed() const { return m_processed; }
	virtual bool isFinished() const;

	virtual void mousePressEvent(QMouseEvent *e) = 0;
	virtual void mouseMoveEvent(QMouseEvent *e) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *e) = 0;
	virtual void mouseDoubleClickEvent(QMouseEvent *e);

protected:
	xActionInterface(xGraphicView *view, QObject *parent, xDef::ActionType type);
	QPointF pointMapToScene(QMouseEvent *e) const;

protected:
	QGraphicsScene *m_scene = nullptr;
	xGraphicView *m_view = nullptr;
	xDef::ActionStatus m_status = xDef::S_Default;
	bool m_isGrabCtrlPoint = false;
	bool m_processed = false;

private:
	xDef::ActionType m_type = xDef::AT_Unknown;
};
