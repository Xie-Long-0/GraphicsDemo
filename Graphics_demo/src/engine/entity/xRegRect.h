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
	// ͨ�������������þ��Σ��贫��scene�����е�ֵ
	void setRect(const QPointF &p1, const QPointF &p2) { setRect(QRectF(p1, p2)); }

	/**
	 * @brief �ƶ�ͼԪ
	 * @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	void moveBy(const QPointF& delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	void moveCtrlPoint(const QPointF& pt, const QPointF& movedPt) override;
	bool isCtrlPoint(const QPointF& p) const override;

	// �ж��Ƿ��Ƿ�Χ��Ե���贫��scene�����е�ֵ
	bool isRegionEdge(const QPointF& p) const override;
	// ͨ�������ı䷶Χ��ȣ��贫��scene�����е�ֵ
	void changeEdgeByPoint(const QPointF& p) override;

protected:
	QRectF m_rect;

private:
	qreal regWidth() const = delete;
	void setRegWidth(qreal w) = delete;
};
