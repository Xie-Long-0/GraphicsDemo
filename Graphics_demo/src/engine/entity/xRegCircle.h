#pragma once

#include "xRegionEntity.h"
#include "xCircle.h"

/**
 * @brief 继承xRegionEntity的带范围圆
*/
class xRegCircle : public xRegionEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegCircle)
	explicit xRegCircle(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const xCircleData &circle, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const QPointF &center, qreal radius, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = ET_RegCircle };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// 额外生成的无范围的圆
	xCircleData subCircleData() const { return m_subCircle->circleData(); }
	// 设置额外生成的圆
	void setSubCircle(const xCircleData &circle);
	// 设置额外生成的圆
	void setSubCircle(const QPointF &center, qreal radius);
	void hideSubCircle(bool hide = true) { m_subCircle->setVisible(!hide); }

	xCircleData circleData() const { return xCircleData(pt1(), pt2(), pt3()); }
	void setCircle(const xCircleData &circle, qreal width) { setCircle(circle.center(), circle.radius(), width); }
	void setCircle(const QPointF &center, qreal radius, qreal width);
	void setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width);

	QPointF center() const { return mapToScene(m_regCircle.center()); }
	void setCenter(const QPointF &center) { moveBy(center - this->center()); }
	qreal radius() const { return m_regCircle.radius(); }
	void setRadius(qreal radius);

	QPointF pt1() const { return mapToScene(m_regCircle.pt1()); }
	QPointF pt2() const { return mapToScene(m_regCircle.pt2()); }
	QPointF pt3() const { return mapToScene(m_regCircle.pt3()); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	void setPt3(const QPointF &p);

	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;
	void changeEdgeByPoint(const QPointF &p) override;
	bool isRegionEdge(const QPointF &p) const override;

protected:
	// 范围圆的数据
	xCircleData m_regCircle;
	// 额外生成的不带范围的圆
	xCircle *m_subCircle = nullptr;
};
