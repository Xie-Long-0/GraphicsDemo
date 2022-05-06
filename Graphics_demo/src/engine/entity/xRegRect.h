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
	// 通过任意两点设置矩形，需传入scene坐标中的值
	void setRect(const QPointF &p1, const QPointF &p2) { setRect(QRectF(p1, p2)); }

	/**
	 * @brief 移动图元
	 * @param delta 移动增量，需传入scene坐标中的值
	*/
	void moveBy(const QPointF& delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF& pt, const QPointF& movedPt) override;
	bool isCtrlPoint(const QPointF& p) const override;

	// 判断是否是范围边缘，需传入scene坐标中的值
	bool isRegionEdge(const QPointF& p) const override;
	// 通过点来改变范围宽度，需传入scene坐标中的值
	void changeEdgeByPoint(const QPointF& p) override;

protected:
	QRectF m_rect;

private:
	qreal regWidth() const = delete;
	void setRegWidth(qreal w) = delete;
};
