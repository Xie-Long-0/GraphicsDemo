#pragma once

#include "xEntity.h"

/**
 * @brief 关联一个图元的基类
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

	xEntity *getBindEntity() const { return m_entity; }
	virtual void bindEntity(xEntity *e);

	QList<QPointF> controlPoints() const override;
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

protected slots:
	virtual void onEntityChanged() = 0;
	virtual void onEntityMoved(const QPointF &delta);

protected:
	QString m_text;
	QPointF m_bindPoint;	// 绑定点
	QPointF m_anchorPoint;	// 锚定点
	qreal m_shiftDist = 0.0;	// 文字偏移距离，往左偏是负数，往右偏是正数
	xEntity *m_entity = nullptr;
};
