#pragma once

#include "xEntity.h"

/**
 * @brief 继承于xEntity的无范围圆
*/
class xCircle : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xCircle)
	explicit xCircle(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const xCircleData &circle, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &center, qreal radius, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = ET_Circle };
	// 重写函数，返回当前的类型值
	int type() const noexcept override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	xCircleData circleData() const noexcept { return m_circle; }
	void setCircle(const xCircleData &circle) { setCircle(circle.center(), circle.radius()); }
	void setCircle(const QPointF &center, qreal radius);
	void setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	QPointF center() const noexcept { return m_circle.center(); }
	void setCenter(const QPointF &center) { moveBy(center - this->center()); }
	qreal radius() const noexcept { return m_circle.radius(); }
	void setRadius(qreal radius);

	QPointF pt1() const noexcept { return m_circle.pt1(); }
	QPointF pt2() const noexcept { return m_circle.pt2(); }
	QPointF pt3() const noexcept { return m_circle.pt3(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	void setPt3(const QPointF &p);

	/**
	 * @brief 移动图元
	 * @param delta 移动增量，需传入scene坐标中的值
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	xCircleData m_circle;
};
