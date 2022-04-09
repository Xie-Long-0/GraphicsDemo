#pragma once

#include "xEntity.h"

/**
 * @brief 关联两个图元的基类
*/
class xInterCoupleEntity : public xEntity
{
	Q_OBJECT

public:
	xInterCoupleEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterCoupleEntity();

	QString text() const { return m_text; }
	void setText(const QString &text);

	void bindEntity1(xEntity *e);
	void bindEntity2(xEntity *e);

protected slots:
	virtual void onEntity1Changed() = 0;
	virtual void onEntity2Changed() = 0;
	virtual void onEntity1Moved(const QPointF &delta) = 0;
	virtual void onEntity2Moved(const QPointF &delta) = 0;

protected:
	QString m_text;
	xEntity *m_entity1 = nullptr;
	xEntity *m_entity2 = nullptr;
};
