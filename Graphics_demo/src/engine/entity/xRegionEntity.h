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
public:
	Q_DISABLE_COPY(xRegionEntity)
	explicit xRegionEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xRegionEntity(qreal width, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xRegionEntity();

	// �ж��Ƿ��Ƿ�Χ��Ե
	virtual bool isRegionEdge(const QPointF &p) const = 0;
	virtual void changeEdgeByPoint(const QPointF &p) = 0;
	//virtual void 

	// ��Χ��ȣ���СΪ������ͼ�ε����һ�ߵľ��루ͨ������¼�ΪͼԪ��Χ��ȵ�һ�룩
	qreal regWidth() const { return m_width; }
	void setRegWidth(qreal w);
	QBrush brush() const { return m_brush; }
	void setBrush(const QBrush &brush);

protected:
	QList<QGraphicsItem *> m_items;
	QBrush m_brush;
	qreal m_width = 0.0;
};
