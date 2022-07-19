#pragma once

#include "xInterSingleEntity.h"

class xArc;
class xRegArc;

/**
 * @brief 关联一个圆弧（或范围圆弧）的图元，继承自xInterSingleEntity
*/
class xInterArc : public xInterSingleEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterArc)
	explicit xInterArc(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterArc(xArc *item, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterArc(xRegArc *item, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// 自定义实体类型枚举
	enum { Type = ET_InterArc };
	// 重写函数，返回当前的类型值
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void bindEntity(xEntity *e) override;

public slots:
	void calculate() override;

protected slots:
	void onEntityChanged() override;
};
