#pragma once

#include "xEntity.h"

/**
 * @brief 关联两个实体的图元基类
*/
class xInterEntity : public xEntity
{
	Q_OBJECT

public:
	xInterEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterEntity();

	QString text() const { return m_text; }
	void setText(const QString &text);

	void setEntity(xEntity *e);
	void setEntity2(xEntity *e);

public slots:
	virtual void onEntity1Changed() = 0;
	virtual void onEntity2Changed() = 0;
	virtual void onEntity1Moved(const QPointF &delta) = 0;
	virtual void onEntity2Moved(const QPointF &delta) = 0;

protected:
	QString m_text;
	xEntity *m_entity = nullptr;
	xEntity *m_entity2 = nullptr;
};
