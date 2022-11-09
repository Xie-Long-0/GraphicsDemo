#pragma once

#include "xEntity.h"
#include <QFont>

/**
 * @brief 关联一个图元的基类
*/
class xInterSingleEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterSingleEntity)
	explicit xInterSingleEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterSingleEntity();

	QString text() const noexcept { return m_text; }
	void setText(const QString &text);
	QPointF bindPoint() const noexcept { return m_bindPoint; }
	void setBindPoint(const QPointF &p);
	QPointF anchorPoint() const noexcept { return m_anchorPoint; }
	void setAnchorPoint(const QPointF &p);
	qreal shiftDistance() const noexcept { return m_shiftDist; }
	void setShiftDistance(qreal dist);

	xEntity *getBindEntity() const noexcept { return m_bindEntity; }
	virtual void bindEntity(xEntity *e);

	/**
	* @brief 移动图元
	* @param delta 移动增量，需传入scene坐标中的值
	*/
	void moveBy(const QPointF &delta) override;
	QList<QPointF> controlPoints() const override;
	/**
	 * @brief 移动图元的一个控制点
	 * @param pt 控制点位置，用于判断哪个控制点，需传入scene坐标中的值
	 * @param movedPt 移动后的点位置，需传入scene坐标中的值
	*/
	void moveCtrlPoint(const QPointF &pt, const QPointF &movedPt) override;
	bool isCtrlPoint(const QPointF &p) const override;

public slots:
	// 用于调用计算任务
	virtual void calculate() = 0;

protected slots:
	// 绑定的图形发生改变
	virtual void onEntityChanged() = 0;
	// 绑定的图形发生移动
	virtual void onEntityMoved(const QPointF &delta);

protected:
	inline void updateTransform();

protected:
	QString m_text;	// 显示文本
	QRectF m_textRect;		// 文本占用的矩形框
	QPointF m_bindPoint;	// 绑定点
	QPointF m_anchorPoint;	// 锚定点
	QTransform m_transform;	// 变换矩阵
	qreal m_rotateAngle = 0;	// 旋转角度（角度）
	qreal m_shiftDist = 0.0;	// 文字偏移距离，往左偏是负数，往右偏是正数
	xEntity *m_bindEntity = nullptr;	// 关联的图元
	QFont m_font;	// 字体
	qreal m_lastFactor = 0;	// 记录上次缩放后的值，当值未改变时不更新文本大小，以减少绘画计算
};

inline void xInterSingleEntity::updateTransform()
{
	m_rotateAngle = 90.0 - Rad2Deg(AnglePoint2Point(m_bindPoint, m_anchorPoint));
	m_transform.reset();
	m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
	m_transform.rotate(m_rotateAngle);
	m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
}

/**
* 
*                            ╱╲
*                          ╱    ╲
*                          ╲       ╲xInterSingleEntity
*                            ╲       ╲
*                     锚定点→╱╲      ╲
*                    　　 　╱    ╲    ╱
*               绑定点    ╱        ╲╱
*                   │  ╱
*              ╱╲ ↓╱╮角度
*            ╱    ╲ ┄┄┄┄┄ 0°
*          ╱ xEntity╲
*          ╲        ╱
*            ╲    ╱
*              ╲╱
* 
*/
