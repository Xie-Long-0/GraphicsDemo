#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include "xTypeDef.h"
#include "xEntity.h"

/**
 * @brief 继承QGraphicsItem与xEntity的带范围的图元虚基类
*/
class xRegionEntity : public xEntity
{
public:
	Q_DISABLE_COPY(xRegionEntity)
	explicit xRegionEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity();

	qreal regWidth() const { return m_width; }
	virtual void setRegWidth(qreal w) = 0;
	QBrush brush() const { return m_brush; }
	virtual void setBrush(const QBrush &brush) = 0;

protected:
	QList<QGraphicsItem *> m_items;
	QBrush m_brush;
	qreal m_width = 0.0;
};
