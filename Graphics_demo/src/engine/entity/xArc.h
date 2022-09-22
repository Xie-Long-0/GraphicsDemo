#pragma once

#include "xEntity.h"

/**
 * @brief 继承自xEntity的无范围圆弧
*/
class xArc : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xArc)
	explicit xArc(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xArc(const xArcData &arc, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = ET_Arc };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	xArcData arcData() const noexcept { return m_arc; }
	void setArc(const xArcData &arc);
	void setArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle);
	void setArc(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	QPointF center() const noexcept { return m_arc.center(); }
	void setCenter(const QPointF &center) { moveBy(center - this->center()); }
	qreal radius() const noexcept { return m_arc.radius(); }
	void setRadius(qreal radius);
	qreal angle() const noexcept { return m_arc.angle(); }
	void setAngle(qreal angle);
	qreal spanAngle() const noexcept { return m_arc.spanAngle(); }
	void setSpanAngle(qreal angle);
	qreal angleDegree() const noexcept { return m_arc.angleDegree(); }
	void setAngleDegree(qreal angle);
	qreal spanAngleDegree() const noexcept { return m_arc.spanAngleDegree(); }
	void setSpanAngleDegree(qreal angle);

	QPointF pt1() const noexcept { return m_arc.pt1(); }
	QPointF pt2() const noexcept { return m_arc.pt2(); }
	QPointF pt3() const noexcept { return m_arc.pt3(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	void setPt3(const QPointF &p);

	/**
	 * @brief 移动图元
	 * @param delta 移动增量，需传入scene坐标中的值
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const noexcept override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	xArcData m_arc;
};
