#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include "xEntity.h"

/**
 * @brief �̳�xEntity�Ĵ���Χ��ͼԪ�����
*/
class xRegionEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegionEntity)
	explicit xRegionEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity() = default;

	// �ж��Ƿ��Ƿ�Χ��Ե���贫��scene�����е�ֵ
	virtual bool isRegionEdge(const QPointF &p) const = 0;
	// ͨ�������ı䷶Χ��ȣ��贫��scene�����е�ֵ
	virtual void changeEdgeByPoint(const QPointF &p) = 0;

	// ��Χ��ȣ���СΪ������ͼ�ε����һ�ߵľ��루ͨ������¼�ΪͼԪ��Χ��ȵ�һ�룩
	qreal regWidth() const noexcept { return m_width; }
	void setRegWidth(qreal w);
	QBrush brush() const noexcept { return m_brush; }
	void setBrush(const QBrush &brush);

signals:
	// ��Χ��ȸı��źţ���setRegWidth��������
	void regWidthChanged(qreal newWidth);

protected:
	QBrush m_brush;
	qreal m_width = 0.0;
};
