#pragma once

#include <QList>
#include <QGraphicsObject>
#include "xTypeDef.h"
#include "xGraphicView.h"

/**
 * @brief ����QGraphicsObject�����л��ʡ���ʽ���źŲ۵�ͼԪ�����
*/
class xEntity : public QGraphicsObject
{
	Q_OBJECT

public:
	enum EntityType {
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
		ET_RegRect,
		ET_Region_End,
		// �󶨵���ͼԪ
		ET_InterSingle_Start,
		ET_InterLine,
		ET_InterCircle,
		ET_InterArc,
		ET_InterPoint,
		ET_InterSingle_End,
		// ������ͼԪ
		ET_InterCouple_Start,
		ET_InterLineAndLine,
		ET_InterLineAndCircle,
		ET_InterLineAndArc,
		ET_InterLineAndPoint,
		ET_InterCircleAndCircle,
		ET_InterCircleAndArc,
		ET_InterCircleAndPoint,
		ET_InterPointAndPoint,
		ET_InterCouple_End
	};
	Q_ENUM(EntityType)

	Q_DISABLE_COPY(xEntity)
	explicit xEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xEntity() = default;
	
	/**
	 * @brief �ƶ�ͼԪ
	 * @param delta �ƶ��������贫��scene�����е�ֵ
	*/
	virtual void moveBy(const QPointF &delta) = 0;
	// ����ͼԪ�Ļ滭���Ƶ�
	virtual QList<QPointF> controlPoints() const noexcept = 0;
	/**
	 * @brief �ƶ�ͼԪ��һ�����Ƶ�
	 * @param pt ���Ƶ�λ�ã������ж��ĸ����Ƶ㣬�贫��scene�����е�ֵ
	 * @param movedPt �ƶ���ĵ�λ�ã��贫��scene�����е�ֵ
	*/
	virtual void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) = 0;
	// �ж��Ƿ��ǿ��Ƶ㣬�贫��scene�����е�ֵ
	virtual bool isCtrlPoint(const QPointF &p) const = 0;

	xDef::EntityStatus status() const noexcept { return m_status; }
	void setStatus(xDef::EntityStatus status) noexcept { m_status = status; }
	QPen pen() const noexcept { return m_pen; }
	void setPen(const QPen &pen);
	xDef::Style style() const noexcept { return m_style; }
	void setStyle(xDef::Style style);

	bool isThisVisible() const noexcept { return isVisible() && opacity() > 0; }
	bool isMovable() const noexcept { return (flags() & ItemIsMovable); }
	bool isSelectable() const noexcept { return (flags() & ItemIsSelectable); }

public slots:
	// ͨ��͸�������ô�ͼԪ�Ŀɼ��ԣ���Ӱ��children�Ŀɼ���
	inline void setThisVisible(bool visible) noexcept;
	inline void showThis() noexcept { setThisVisible(true); }
	inline void hideThis() noexcept { setThisVisible(false); }
	inline void setMovable(bool b) noexcept;
	inline void setSelectable(bool b) noexcept;

signals:
	void selectedChanged(bool selected);
	void cursorChanged(const QCursor &newCursor);
	void flagsChanged(const GraphicsItemFlags &newFlags);
	// λ�øı��źţ���moveBy��������
	void posChanged(const QPointF &delta);
	// ��״�ı��ź�
	void shapeChanged();

protected:
	// ���ڴ������QGraphicsItem���ݵĸı䣬������Ӧ�ź�
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	// ��ȡ��ͼ������ϵ��
	inline qreal viewScaleFactor() const noexcept;

	QPen m_pen;
	xDef::Style m_style = xDef::S_NoStyle;
	xDef::EntityStatus m_status = xDef::ES_Init;
	xGraphicView *m_view = nullptr;

private:
	inline void init() noexcept;
};

inline void xEntity::init() noexcept
{
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	// ����parent��͸���ȣ���ʵ��parent���ɼ���children�ɼ�
	setFlag(ItemIgnoresParentOpacity);
	setAcceptHoverEvents(true);
}

inline void xEntity::setThisVisible(bool visible) noexcept
{
	if (visible)
		setOpacity(1.0);
	else
		setOpacity(0);
}

inline void xEntity::setMovable(bool b) noexcept
{
	if (b)
		setFlag(ItemIsMovable, true);
	else
		setFlag(ItemIsMovable, false);
}

inline void xEntity::setSelectable(bool b) noexcept
{
	if (b)
		setFlag(ItemIsSelectable, true);
	else
		setFlag(ItemIsSelectable, false);
}

inline qreal xEntity::viewScaleFactor() const noexcept
{
	if (m_view == nullptr) return 1.0;
	return m_view->scaleFactor();
}
