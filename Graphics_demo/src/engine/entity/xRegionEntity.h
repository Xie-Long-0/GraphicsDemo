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
	xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity();

	// 判断是否是范围边缘
	virtual bool isRegionEdge(const QPointF &p) const = 0;
	virtual void changeEdgeByPoint(const QPointF &p) = 0;
	//virtual void 

	// 范围宽度，大小为从中心图形到最大一边的距离（通常情况下即为图元范围宽度的一半）
	qreal regWidth() const { return m_width; }
	void setRegWidth(qreal w);
	QBrush brush() const { return m_brush; }
	void setBrush(const QBrush &brush);

protected:
	QList<QGraphicsItem *> m_items;
	QBrush m_brush;
	qreal m_width = 0.0;
};
