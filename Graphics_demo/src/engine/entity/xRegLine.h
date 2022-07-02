#pragma once

#include "xRegionEntity.h"
#include "xLine.h"

/**
 * @brief �̳�xRegionEntity�Ĵ���Χֱ��
*/
class xRegLine : public xRegionEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegLine)
	explicit xRegLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegLine(const QLineF &line, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegLine(const QPointF &p1, const QPointF &p2, qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	~xRegLine();

	// �Զ���ʵ������ö��
	enum { Type = ET_RegLine };
	// ��д���������ص�ǰ������ֵ
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// �������ɵ��޷�Χ����
	auto subLineData() const noexcept { return m_subLine; }
	// ���ö������ɵ���
	void setSubLine(const QLineF &line);
	// ���ö������ɵ���
	void setSubLine(const QPointF &p1, const QPointF &p2);
	void hideSubLine(bool hide = true) noexcept { m_subLine->setVisible(!hide); }

	QLineF lineData() const noexcept { return m_regLine; }
	void setLine(const QLineF &line, qreal width) { setLine(line.p1(), line.p2(), width); }
	void setLine(const QPointF &p1, const QPointF &p2, qreal width);

	QPointF pt1() const noexcept { return m_regLine.p1(); }
	QPointF pt2() const noexcept { return m_regLine.p2(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	QPointF middlePoint() const noexcept { return (pt1() + pt2()) * 0.5; }

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
	// ��Χ�ߵ�����
	QLineF m_regLine;
	// �������ɵĲ�����Χ����
	xLine *m_subLine = nullptr;
};
