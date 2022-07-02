#pragma once

#include "xEntity.h"

/**
 * @brief ��������ͼԪ�Ļ���
*/
class xInterCoupleEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterCoupleEntity)
	explicit xInterCoupleEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterCoupleEntity(xEntity *item1, xEntity *item2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterCoupleEntity();

	QString text() const noexcept { return m_text; }
	void setText(const QString &text);
	QPointF bindPoint1() const noexcept { return m_bindPoint1; }
	void setBindPoint1(const QPointF &p);
	QPointF bindPoint2() const noexcept { return m_bindPoint2; }
	void setBindPoint2(const QPointF &p);
	QPointF anchorPoint() const noexcept { return m_anchorPoint; }
	void setAnchorPoint(const QPointF &p);
	qreal shiftDistance() const noexcept { return m_shiftDist; }
	void setShiftDistance(qreal dist);

	xEntity *getBindEntity1() const noexcept { return m_bindEntity1; }
	xEntity *getBindEntity2() const noexcept { return m_bindEntity2; }
	virtual void bindEntity1(xEntity *e);
	virtual void bindEntity2(xEntity *e);

	/**
	 * @brief �ƶ�ͼԪ
	 * @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const noexcept override;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected slots:
	virtual void onEntity1Changed() = 0;
	virtual void onEntity2Changed() = 0;
	virtual void onEntity1Moved(const QPointF &delta);
	virtual void onEntity2Moved(const QPointF &delta);

protected:
	QString m_text;	// ��ʾ�ı�
	QRectF m_textRect;		// �ı�ռ�õľ��ο�
	QPointF m_bindPoint1;	// �󶨵�1
	QPointF m_bindPoint2;	// �󶨵�2
	QPointF m_anchorPoint;	// ê����
	QTransform m_transform;	// �任����
	qreal m_rotateAngle = 0;	// ��ת�Ƕȣ����ȣ�
	qreal m_shiftDist = 0.0;	// ����ƫ�ƾ��룬����ƫ�Ǹ���������ƫ������
	xEntity *m_bindEntity1 = nullptr;	// ������ͼԪ1
	xEntity *m_bindEntity2 = nullptr;	// ������ͼԪ2
	QFont m_font;	// ����
	qreal m_lastFactor = 0;	// ��¼�ϴ����ź��ֵ����ֵδ�ı�ʱ�������ı���С���Լ��ٻ滭����
};

/**
* 
*                       +-------------------+
*               ƫ�ơ�  |       Text        | xInterCoupleEntity
*                -------+---------x---------+
*                  ��        ��   ��
*                  ��        ��   ê����
*                 +--+      +--+
*                 |��|      |��|
*                 |��|      |��|
*       �󶨵��  |��|      |��|
*                 |  |      |  |
*                 |  |      |  |
*                 +--+      +--+
* 
*/
