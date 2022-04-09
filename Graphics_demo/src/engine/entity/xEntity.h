#pragma once

#include <QList>
#include <QGraphicsObject>
#include "xTypeDef.h"
#include "xStyle.h"
#include "xGraphicView.h"

/**
 * @brief ����QGraphicsItem�Ĵ��л��ʺ���ʽ��ͼԪ�����
*/
class xEntity : public QGraphicsObject
{
	Q_OBJECT

public:
	enum {
		ET_Unknown = UserType,
		// ������Χ��ͼԪ
		ET_Entity_Start,
		ET_Line,
		ET_Circle,
		ET_Arc,
		ET_Point,
		ET_Entity_End,
		// ����Χ��ͼԪ
		ET_Region_Start,
		ET_RegLine,
		ET_RegCircle,
		ET_RegArc,
		ET_RegPoint,
		ET_Region_End
	};

	Q_DISABLE_COPY(xEntity)
	explicit xEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xEntity() = default;

	// �ƶ�ͼԪ��deltaΪ�ƶ�����
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

signals:
	// λ�øı��źţ���moveBy��������
	void posChanged(const QPointF &delta);
	// ��״�ı��ź�
	void shapeChanged();
	void selectedChanged(bool selected);
	void cursorChanged(const QCursor &newCursor);
	void flagsChanged(const GraphicsItemFlags &newFlags);

protected:
	// ���ڴ������QGraphicsItem���ݵĸı䣬������Ӧ�ź�
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
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
