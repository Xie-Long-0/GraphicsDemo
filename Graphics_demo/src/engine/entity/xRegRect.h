#pragma once

#include "xRegionEntity.h"

class xRegRect : public xRegionEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegRect)
	xRegRect(xGraphicView* view, QGraphicsItem* parent = nullptr);
	xRegRect(const QRectF& rect, xGraphicView* view, QGraphicsItem* parent = nullptr);
	xRegRect(const QPointF& topleft, const QPointF &botright, xGraphicView* view, QGraphicsItem* parent = nullptr);
	~xRegRect();

	// 自定义实体类型枚举
	enum { Type = ET_RegRect };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	QRectF rect() const { return m_rect; }
	void setRect(const QRectF& rect);

	void moveBy(const QPointF& delta) override;
	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF& pt, const QPointF& movedPt) override;
	bool isCtrlPoint(const QPointF& p) const override;

	// 判断是否是范围边缘
	virtual bool isRegionEdge(const QPointF& p) const override;
	// 通过点到中心图形的距离来设置范围宽度
	virtual void changeEdgeByPoint(const QPointF& p) override;

protected:
	QRectF m_rect;

private:
	qreal regWidth() const = delete;
	void setRegWidth(qreal w) = delete;
};
