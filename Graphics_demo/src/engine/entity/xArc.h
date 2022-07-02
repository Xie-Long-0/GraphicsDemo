#pragma once

#include "xEntity.h"

/**
 * @brief �̳���xEntity���޷�ΧԲ��
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

	// �Զ���ʵ������ö��
	enum { Type = ET_Arc };
	// ��д���������ص�ǰ������ֵ
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

	QPointF pt1() const noexcept { return m_arc.pt1(); }
	QPointF pt2() const noexcept { return m_arc.pt2(); }
	QPointF pt3() const noexcept { return m_arc.pt3(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	void setPt3(const QPointF &p);

	/**
	 * @brief �ƶ�ͼԪ
	 * @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const noexcept override;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	xArcData m_arc;
};
