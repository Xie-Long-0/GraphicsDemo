#pragma once

#include "xEntity.h"
#include <QFont>

/**
 * @brief ����һ��ͼԪ�Ļ���
*/
class xInterSingleEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterSingleEntity)
	explicit xInterSingleEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterSingleEntity(xEntity *item, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterSingleEntity();

	QString text() const { return m_text; }
	void setText(const QString &text);
	QPointF bindPoint() const { return m_bindPoint; }
	void setBindPoint(const QPointF &p);
	QPointF anchorPoint() const { return m_anchorPoint; }
	void setAnchorPoint(const QPointF &p);
	qreal shiftDistance() const { return m_shiftDist; }
	void setShiftDistance(qreal dist);

	xEntity *getBindEntity() const { return m_bindEntity; }
	virtual void bindEntity(xEntity *e);

	/**
	* @brief �ƶ�ͼԪ
	* @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected slots:
	virtual void onEntityChanged() = 0;
	virtual void onEntityMoved(const QPointF &delta);

protected:
	QString m_text;	// ��ʾ�ı�
	QRectF m_textRect;		// �ı�ռ�õľ��ο�
	QPointF m_bindPoint;	// �󶨵�
	QPointF m_anchorPoint;	// ê����
	QTransform m_transform;	// �任����
	qreal m_rotateAngle = 0;	// ��ת�Ƕȣ����ȣ�
	qreal m_shiftDist = 0.0;	// ����ƫ�ƾ��룬����ƫ�Ǹ���������ƫ������
	xEntity *m_bindEntity = nullptr;	// ������ͼԪ
	QFont m_font;	// ����
	qreal m_lastFactor = 0;	// ��¼�ϴ����ź��ֵ����ֵδ�ı�ʱ�������ı���С���Լ��ٻ滭����
};

/**
* 
*                               �u�v
*                    ƫ�ơ� �v�u    �vxInterSingleEntity
*                             �v      �v
*                     ê������u�v      �v
*                    ���� ���u    �v    �u
*               �󶨵�    �u        �v�u
*                   ��  �u
*              �u�v ���u�r�Ƕ�
*            �u    �v ���������� 0��
*          �u xEntity�v
*          �v        �u
*            �v    �u
*              �v�u
* 
*/
