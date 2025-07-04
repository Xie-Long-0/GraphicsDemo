#pragma once

#include "xEntity.h"

/**
 * @brief 关联两个图元的基类
*/
class xInterCoupleEntity : public xEntity
{
	Q_OBJECT

public:
	Q_DISABLE_COPY(xInterCoupleEntity)
	explicit xInterCoupleEntity(xGraphicView *view, QGraphicsItem *parent = nullptr);
	xInterCoupleEntity(xEntity *item1, xEntity *item2, xGraphicView *view, QGraphicsItem *parent = nullptr);
	virtual ~xInterCoupleEntity();

	QString text() const noexcept { return m_text; }
	void setText(const QString &text);
	QPointF bindPoint1() const noexcept { return m_bindPoint1; }
	void setBindPoint1(const QPointF &p);
	QPointF bindPoint2() const noexcept { return m_bindPoint2; }
	void setBindPoint2(const QPointF &p);
	QPointF anchorPoint() const noexcept { return m_anchorPoint; }
	void setAnchorPoint(const QPointF &p);
	qreal shiftDistance() const noexcept { return m_shiftDist; }
	void setShiftDistance(qreal dist);

	xEntity *getBindEntity1() const noexcept { return m_bindEntity1; }
	xEntity *getBindEntity2() const noexcept { return m_bindEntity2; }
	virtual void bindEntity1(xEntity *e);
	virtual void bindEntity2(xEntity *e);

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
	virtual void onEntity1Changed() = 0;
	virtual void onEntity2Changed() = 0;
	virtual void onEntity1Moved(const QPointF &delta);
	virtual void onEntity2Moved(const QPointF &delta);

protected:
    inline void updateTransform();

protected:
	QString m_text;	// 显示文本
	QRectF m_textRect;		// 文本占用的矩形框
	QPointF m_bindPoint1;	// 绑定点1
	QPointF m_bindPoint2;	// 绑定点2
	QPointF m_anchorPoint;	// 锚定点
	QTransform m_transform;	// 变换矩阵
	qreal m_rotateAngle = 0;	// 旋转角度（弧度）
	qreal m_shiftDist = 0.0;	// 文字偏移距离，往左偏是负数，往右偏是正数
	xEntity *m_bindEntity1 = nullptr;	// 关联的图元1
	xEntity *m_bindEntity2 = nullptr;	// 关联的图元2
	QFont m_font;	// 字体
	qreal m_lastFactor = 0;	// 记录上次缩放后的值，当值未改变时不更新文本大小，以减少绘画计算
};

inline void xInterCoupleEntity::updateTransform()
{
    //m_rotateAngle = 90.0 - Rad2Deg(AnglePoint2Point(m_bindPoint, m_anchorPoint));
    //m_transform.reset();
    //m_transform.translate(m_bindPoint.x(), m_bindPoint.y());
    //m_transform.rotate(m_rotateAngle);
    //m_transform.translate(-m_bindPoint.x(), -m_bindPoint.y());
}

/**
* 
*                       +-------------------+
*               偏移↓  |       Text        | xInterCoupleEntity
*                -------+---------x---------+
*                  ┆        ┆   ↑
*                  ┆        ┆   锚定点
*                 +--+      +--+
*                 |┆|      |┆|
*                 |┆|      |┆|
*       绑定点→  |┆|      |┆|
*                 |  |      |  |
*                 |  |      |  |
*                 +--+      +--+
* 
*/
