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

	// �Զ���ʵ������ö��
	enum { Type = ET_RegArc };
	// ��д���������ص�ǰ������ֵ
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// �������ɵ��޷�Χ��Բ
	auto subArc() const noexcept { return m_subArc; }
	// ���ö������ɵ�Բ
	void setSubArc(const xArcData &arc);
	// ���ö������ɵ�Բ
	void setSubArc(const QPointF &center, qreal radius, qreal angle, qreal spanAngle);
	void hideSubArc(bool hide = true) noexcept { m_subArc->setVisible(!hide); }

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
	// ͨ�������ı䷶Χ��ȣ��贫��scene�����е�ֵ
	void changeEdgeByPoint(const QPointF &p) override;
	// �ж��Ƿ��Ƿ�Χ��Ե���贫��scene�����е�ֵ
	bool isRegionEdge(const QPointF &p) const override;

protected:
	// ��ΧԲ��������
	xArcData m_arc;
	// ���ɵ�Բ��
	xArc *m_subArc = nullptr;
};
