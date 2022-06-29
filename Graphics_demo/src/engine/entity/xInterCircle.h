#pragma once

#include "xInterSingleEntity.h"

class xCircle;
class xRegCircle;

/**
 * @brief 关联一个圆（或范围圆）的图元，继承自xInterSingleEntity
*/
class xInterCircle : public xInterSingleEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterCircle)
	explicit xInterCircle(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterCircle(xCircle *item, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterCircle(xRegCircle *item, xGraphicView *view, QGraphicsItem *parent = nullptr);

	~xInterCircle();

	enum { Type = ET_InterCircle };
	int type() const override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void bindEntity(xEntity *e) override;

protected slots:
	void onEntityChanged() override;

protected:
	bool m_use2Line = false;
};
