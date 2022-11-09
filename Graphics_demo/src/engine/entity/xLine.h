#pragma once

#include "xEntity.h"
#include <QLineF>

/**
 * @brief 继承于xEntity的无范围直线
*/
class xLine : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xLine)
	explicit xLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QLineF &line, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QPointF &p1, const QPointF &p2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	
	// 自定义实体类型枚举
	enum { Type = ET_Line };
	// 重写函数，返回当前的类型值
	int type() const noexcept override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	QLineF lineData() const noexcept { return m_line; }
	void setLine(const QLineF &line) { setLine(line.p1(), line.p2()); }
	void setLine(const QPointF &p1, const QPointF &p2);

	QPointF pt1() const noexcept { return m_line.p1(); }
	QPointF pt2() const noexcept { return m_line.p2(); }
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);
	QPointF middlePoint() const noexcept { return (pt1() + pt2()) * 0.5; }
	
	/**
	 * @brief 移动图元
	 * @param delta 移动增量，需传入scene坐标中的值
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	QLineF m_line;
};
