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
	QLineF subLineData() const { return m_subLine->lineData(); }
	// ���ö������ɵ���
	void setSubLine(const QLineF &line);
	// ���ö������ɵ���
	void setSubLine(const QPointF &p1, const QPointF &p2);
	void hideSubLine(bool hide = true) { m_subLine->setVisible(!hide); }

	QLineF lineData() const { return QLineF(pt1(), pt2()); }
	void setLine(const QLineF &line, qreal width) { setLine(line.p1(), line.p2(), width); }
	void setLine(const QPointF &p1, const QPointF &p2, qreal width);

	QPointF pt1() const { return mapToScene(m_regLine.p1()); }
	QPointF pt2() const { return mapToScene(m_regLine.p2()); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	QPointF middlePoint() const { return (pt1() + pt2()) * 0.5; }

	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;
	void changeEdgeByPoint(const QPointF &p) override;
	bool isRegionEdge(const QPointF &p) const override;

protected:
	// ��Χ�ߵ�����
	QLineF m_regLine;
	// �������ɵĲ�����Χ����
	xLine *m_subLine = nullptr;
};
