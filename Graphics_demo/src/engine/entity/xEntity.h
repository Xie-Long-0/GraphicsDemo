#pragma once

#include <QList>
#include <QGraphicsItem>
#include "xTypeDef.h"
#include "xStyle.h"
#include "xGraphicView.h"

/**
 * @brief ����QGraphicsItem�Ĵ��л��ʺ���ʽ��ͼԪ�����
*/
class xEntity : public QGraphicsItem
{
public:
	Q_DISABLE_COPY(xEntity)
	explicit xEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xEntity() = default;

	// �ƶ�ͼԪ
	virtual void moveBy(const QPointF &delta) = 0;
	// ����ͼԪ�Ļ滭���Ƶ�
	virtual QList<QPointF> controlPoints() const = 0;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ͼԪ�ϵĿ��Ƶ�
	 * @param movedPt �ƶ���ĵ�λ��
	*/
	virtual void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) = 0;
	// �ж��Ƿ��ǿ��Ƶ�
	virtual bool isCtrlPoint(const QPointF &p) const = 0;

	QPen pen() const { return m_pen; }
	void setPen(const QPen &pen);
	xStyle::Style style() const { return m_style; }
	void setStyle(xStyle::Style style);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
	// ��ȡ��ͼ������ϵ��
	inline qreal viewScaleFactor() const;

	QPen m_pen;
	xStyle::Style m_style = xStyle::NoStyle;
	xGraphicView *m_view = nullptr;

private:
	inline void init();
};

inline void xEntity::init()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}

inline qreal xEntity::viewScaleFactor() const
{
	// ͨ��view��ת�������ȡ����ϵ����m11��ŵ�ֵ��ʾ���ű���
	return m_view->transform().m11();
}
