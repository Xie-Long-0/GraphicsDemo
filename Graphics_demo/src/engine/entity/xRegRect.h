#pragma once

#include "xRegionEntity.h"

class xRegRect : public xRegionEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegRect)
	xRegRect(xGraphicView* view, QGraphicsItem* parent = nullptr);
	xRegRect(const QRectF& rect, xGraphicView* view, QGraphicsItem* parent = nullptr);
	xRegRect(const QPointF& topleft, const QPointF &botright, xGraphicView* view, QGraphicsItem* parent = nullptr);
	~xRegRect();

	// �Զ���ʵ������ö��
	enum { Type = ET_RegRect };
	// ��д���������ص�ǰ������ֵ
	int type() const override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	QRectF rect() const { return m_rect; }
	void setRect(const QRectF& rect);

	void moveBy(const QPointF& delta) override;
	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF& pt, const QPointF& movedPt) override;
	bool isCtrlPoint(const QPointF& p) const override;

	// �ж��Ƿ��Ƿ�Χ��Ե
	virtual bool isRegionEdge(const QPointF& p) const override;
	// ͨ���㵽����ͼ�εľ��������÷�Χ���
	virtual void changeEdgeByPoint(const QPointF& p) override;

protected:
	QRectF m_rect;

private:
	qreal regWidth() const = delete;
	void setRegWidth(qreal w) = delete;
};
