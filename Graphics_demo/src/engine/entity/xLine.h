#pragma once

#include <QGraphicsLineItem>
#include "xTypeDef.h"
#include "xStyle.h"
#include "xEntity.h"

/**
 * @brief 继承自QGraphicsLineItem的无范围直线
*/
class xLine : public QGraphicsLineItem, public xEntity
{
public:
	explicit xLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QLineF &line, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(qreal x1, qreal y1, qreal x2, qreal y2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xLine(const QPointF &p1, const QPointF &p2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	
	// 自定义实体类型枚举
	enum { Type = xDef::ET_Line };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

	QLineF lineData() const;
	using QGraphicsLineItem::setLine;
	void setLine(const QPointF &p1, const QPointF &p2) { setLine(QLineF(p1, p2)); }

	void setPen(const QPen &pen) override;
	void setStyle(xStyle::Style style) override;

	QPointF pt1() const;
	QPointF pt2() const;
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);

	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected:
	inline void init();

private:
	using QGraphicsLineItem::line;
	Q_DISABLE_COPY(xLine)
};

inline void xLine::init()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}
