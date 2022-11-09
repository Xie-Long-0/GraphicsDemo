#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include "xEntity.h"

/**
 * @brief 继承xEntity的带范围的图元虚基类
*/
class xRegionEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegionEntity)
	explicit xRegionEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity();

	// 判断是否是范围边缘，需传入scene坐标中的值
	virtual bool isRegionEdge(const QPointF &p) const = 0;
	// 通过点来改变范围宽度，需传入scene坐标中的值
	virtual void changeEdgeByPoint(const QPointF &p) = 0;

	// 范围宽度，大小为从中心图形到最大一边的距离（通常情况下即为图元范围宽度的一半）
	qreal regWidth() const noexcept { return m_width; }
	void setRegWidth(qreal w);
	QBrush brush() const noexcept { return m_brush; }
	void setBrush(const QBrush &brush);

signals:
	// 范围宽度改变信号，由setRegWidth函数发送
	void regWidthChanged(qreal newWidth);

protected:
	QBrush m_brush;
	qreal m_width = 0.0;
};
