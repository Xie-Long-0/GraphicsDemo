#pragma once

#include <QGraphicsItem>
#include <QBrush>
#include "xTypeDef.h"
#include "xEntity.h"

/**
 * @brief �̳�QGraphicsItem��xEntity�Ĵ���Χ��ͼԪ�����
*/
class xRegionEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xRegionEntity)
	explicit xRegionEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity() = default;

	// �ж��Ƿ��Ƿ�Χ��Ե
	virtual bool isRegionEdge(const QPointF &p) const = 0;
	// ͨ���㵽����ͼ�εľ��������÷�Χ���
	virtual void changeEdgeByPoint(const QPointF &p) = 0;

	// ��Χ��ȣ���СΪ������ͼ�ε����һ�ߵľ��루ͨ������¼�ΪͼԪ��Χ��ȵ�һ�룩
	qreal regWidth() const { return m_width; }
	void setRegWidth(qreal w);
	QBrush brush() const { return m_brush; }
	void setBrush(const QBrush &brush);

signals:
	// ��Χ��ȸı��źţ���setRegWidth��������
	void regWidthChanged(qreal newWidth);

protected:
	QBrush m_brush;
	qreal m_width = 0.0;
};
