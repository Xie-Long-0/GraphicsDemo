#pragma once

#include "xRegionEntity.h"

/**
 * @brief 继承xRegionEntity的带范围直线
*/
class xRegLine : public xRegionEntity
{
public:
	Q_DISABLE_COPY(xRegLine)
	explicit xRegLine(xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = xDef::ET_RegCircle };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void setRegWidth(qreal w) override;
	QLineF lineData() const { return QLineF(pt1(), pt2()); }
	void setLine(const QLineF &line);
	void setLine(const QPointF &p1, const QPointF &p2) { setLine(QLineF(p1, p2)); }
	QPointF pt1() const { return mapToScene(m_line.p1()); }
	QPointF pt2() const { return mapToScene(m_line.p2()); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);

	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	QLineF m_line;
};
