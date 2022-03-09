#pragma once

#include <QGraphicsItem>
#include "xTypeDef.h"
#include "xStyle.h"

class xCircle : public QGraphicsItem
{
public:
	xCircle(QGraphicsItem *parent = nullptr);

	enum { Type = xDef::ET_Circle };
	int type() const override;

protected:
	xStyle::Style m_style = xStyle::NoStyle;
	QPen m_pen;
	QPointF m_center;
	qreal m_radius = 0.0;
};
