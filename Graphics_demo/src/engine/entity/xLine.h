#pragma once

#include <QGraphicsLineItem>
#include "xTypeDef.h"
#include "xStyle.h"

/**
 * @brief 继承自QGraphicsLineItem的无范围直线
*/
class xLine : public QGraphicsLineItem
{
public:
	xLine(QGraphicsItem *parent = nullptr);
	xLine(const QLineF &line, QGraphicsItem *parent = nullptr);
	xLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);
	xLine(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent = nullptr);
	
	// 自定义实体类型枚举
	enum { Type = xDef::ET_Line };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

	QLineF line() const;
	using QGraphicsLineItem::setLine;
	void setLine(const QPointF &p1, const QPointF &p2) { setLine(QLineF(p1, p2)); }

	xStyle::Style style() const { return m_style; }
	void setStyle(xStyle::Style style) { m_style = style; }

	QPointF pt1() const;
	QPointF pt2() const;
	void setPt1(const QPointF &p);
	void setPt2(const QPointF &p);

protected:
	inline void init();
	// 获取视图的缩放系数
	qreal viewScaleFactor() const;

	xStyle::Style m_style = xStyle::NoStyle;
	QPen m_pen;

private:
	using QGraphicsLineItem::setPen;
	using QGraphicsLineItem::line;
};
