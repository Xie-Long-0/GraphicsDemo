#pragma once

#include "xRegionEntity.h"
#include "xCircle.h"

/**
 * @brief �̳�xRegionEntity�Ĵ���ΧԲ
*/
class xRegCircle : public xRegionEntity
{
public:
	Q_DISABLE_COPY(xRegCircle)
	explicit xRegCircle(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const xCircleData &circle, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const QPointF &center, qreal radius, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// �Զ���ʵ������ö��
	enum { Type = xDef::ET_RegCircle };
	// ��д���������ص�ǰ������ֵ
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	xCircleData circleData() const { return xCircleData(pt1(), pt2(), pt3()); }
	void setCircle(const xCircleData &circle) { setCircle(circle.center(), circle.radius()); }
	void setCircle(const QPointF &center, qreal radius);
	void setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	QPointF center() const { return mapToScene(m_regCircle.center()); }
	void setCenter(const QPointF &center);
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
	// ��ΧԲ������
	xCircleData m_regCircle;
	// �������ɵĲ�����Χ��Բ
	xCircle *m_subCircle = nullptr;
};