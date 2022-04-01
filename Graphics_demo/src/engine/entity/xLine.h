#pragma once

#include "xEntity.h"
#include <QLineF>

/**
 * @brief 继承于xEntity的无范围直线
*/
class xLine : public xEntity
{
public:
	Q_DISABLE_COPY(xLine)
	explicit xLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QLineF &line, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QPointF &p1, const QPointF &p2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	
	// 自定义实体类型枚举
	enum { Type = xDef::ET_Line };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	QLineF lineData() const { return QLineF(pt1(), pt2()); }
	void setLine(const QLineF &line) { setLine(line.p1(), line.p2()); }
	void setLine(const QPointF &p1, const QPointF &p2);

	QPointF pt1() const { return mapToScene(m_line.p1()); }
	QPointF pt2() const { return mapToScene(m_line.p2()); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);

	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	QLineF m_line;
};
