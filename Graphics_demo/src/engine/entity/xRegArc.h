#pragma once

#include "xRegionEntity.h"
#include "xArc.h"

class xRegArc : public xRegionEntity
{
	Q_OBJECT

public:
	explicit xRegArc(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegArc(const xArcData &arc, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = ET_RegArc };
	// 重写函数，返回当前的类型值
	int type() const noexcept override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// 额外生成的无范围的圆
	auto subArc() const noexcept { return m_subArc; }
	// 设置额外生成的圆
	void setSubArc(const xArcData &arc);
	// 设置额外生成的圆
	void setSubArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle);
	void hideSubArc(bool hide = true) { m_subArc->setVisible(!hide); }

	xArcData arcData() const noexcept { return m_arc; }
	void setArc(const xArcData &arc, qreal width);
	void setArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle, qreal width);
	void setArc(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width);

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
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;
	// 通过点来改变范围宽度，需传入scene坐标中的值
	void changeEdgeByPoint(const QPointF &p) override;
	// 判断是否是范围边缘，需传入scene坐标中的值
	bool isRegionEdge(const QPointF &p) const override;

protected:
	// 范围圆弧的数据
	xArcData m_arc;
	// 生成的圆弧
	xArc *m_subArc = nullptr;
};
