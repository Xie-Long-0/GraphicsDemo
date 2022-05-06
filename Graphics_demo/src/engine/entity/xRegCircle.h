#pragma once

#include "xRegionEntity.h"
#include "xCircle.h"

/**
 * @brief �̳�xRegionEntity�Ĵ���ΧԲ
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

	// �Զ���ʵ������ö��
	enum { Type = ET_RegCircle };
	// ��д���������ص�ǰ������ֵ
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// �������ɵ��޷�Χ��Բ
	xCircleData subCircleData() const { return m_subCircle->circleData(); }
	// ���ö������ɵ�Բ
	void setSubCircle(const xCircleData &circle);
	// ���ö������ɵ�Բ
	void setSubCircle(const QPointF &center, qreal radius);
	void hideSubCircle(bool hide = true) { m_subCircle->setVisible(!hide); }

	xCircleData circleData() const { return m_regCircle; }
	void setCircle(const xCircleData &circle, qreal width) { setCircle(circle.center(), circle.radius(), width); }
	void setCircle(const QPointF &center, qreal radius, qreal width);
	void setCircle(const QPointF &p1, const QPointF &p2, const QPointF &p3, qreal width);

	QPointF center() const { return m_regCircle.center(); }
	void setCenter(const QPointF &center) { moveBy(center - this->center()); }
	qreal radius() const { return m_regCircle.radius(); }
	void setRadius(qreal radius);

	QPointF pt1() const { return m_regCircle.pt1(); }
	QPointF pt2() const { return m_regCircle.pt2(); }
	QPointF pt3() const { return m_regCircle.pt3(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	void setPt3(const QPointF &p);

	/**
	 * @brief �ƶ�ͼԪ
	 * @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;
	// ͨ�������ı䷶Χ��ȣ��贫��scene�����е�ֵ
	void changeEdgeByPoint(const QPointF &p) override;
	// �ж��Ƿ��Ƿ�Χ��Ե���贫��scene�����е�ֵ
	bool isRegionEdge(const QPointF &p) const override;

protected:
	// ��ΧԲ������
	xCircleData m_regCircle;
	// �������ɵĲ�����Χ��Բ
	xCircle *m_subCircle = nullptr;
};
