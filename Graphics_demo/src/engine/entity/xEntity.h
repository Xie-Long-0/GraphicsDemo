#pragma once

#include <QList>
#include <QPoint>
#include "xStyle.h"

class xGraphicView;

class xEntity
{
public:
	explicit xEntity(xGraphicView *view);
	virtual QList<QPointF> controlPoints() const = 0;
	virtual void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) = 0;
	virtual bool isCtrlPoint(const QPointF &p) const = 0;

	QPen pen() const { return m_pen; }
	virtual void setPen(const QPen &pen) = 0;
	xStyle::Style style() const { return m_style; }
	virtual void setStyle(xStyle::Style style) = 0;

protected:
	// 获取视图的缩放系数
	qreal viewScaleFactor() const;

	QPen m_pen;
	xStyle::Style m_style = xStyle::NoStyle;
	xGraphicView *m_view = nullptr;
};
