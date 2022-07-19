#pragma once

#include "xInterSingleEntity.h"

class xArc;
class xRegArc;

/**
 * @brief ����һ��Բ������ΧԲ������ͼԪ���̳���xInterSingleEntity
*/
class xInterArc : public xInterSingleEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterArc)
	explicit xInterArc(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterArc(xArc *item, xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterArc(xRegArc *item, xGraphicView *view, QGraphicsItem *parent = nullptr);

	// �Զ���ʵ������ö��
	enum { Type = ET_InterArc };
	// ��д���������ص�ǰ������ֵ
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
