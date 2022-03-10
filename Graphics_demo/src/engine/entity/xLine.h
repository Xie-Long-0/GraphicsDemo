#pragma once

#include <QGraphicsLineItem>
#include "xTypeDef.h"
#include "xStyle.h"

/**
 * @brief �̳���QGraphicsLineItem���޷�Χֱ��
*/
class xLine : public QGraphicsLineItem
{
public:
	xLine(QGraphicsItem *parent = nullptr);
	xLine(const QLineF &line, QGraphicsItem *parent = nullptr);
	xLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);
	xLine(const QPointF &p1, const QPointF &p2, QGraphicsItem *parent = nullptr);
	
	// �Զ���ʵ������ö��
	enum { Type = xDef::ET_Line };
	// ��д���������ص�ǰ������ֵ
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
	// ��ȡ��ͼ������ϵ��
	qreal viewScaleFactor() const;

	xStyle::Style m_style = xStyle::NoStyle;
	QPen m_pen;

private:
	using QGraphicsLineItem::setPen;
	using QGraphicsLineItem::line;
};
