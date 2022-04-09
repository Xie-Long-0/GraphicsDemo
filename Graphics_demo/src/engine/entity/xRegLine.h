#pragma once

#include "xRegionEntity.h"
#include "xLine.h"

/**
 * @brief 继承xRegionEntity的带范围直线
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

	// 自定义实体类型枚举
	enum { Type = ET_RegLine };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	// 额外生成的无范围的线
	QLineF subLineData() const { return m_subLine->lineData(); }
	// 设置额外生成的线
	void setSubLine(const QLineF &line);
	// 设置额外生成的线
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
	// 范围线的数据
	QLineF m_regLine;
	// 额外生成的不带范围的线
	xLine *m_subLine = nullptr;
};
