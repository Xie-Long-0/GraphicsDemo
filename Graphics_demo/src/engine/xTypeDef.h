#pragma once

#include <cmath>
#include <qobjectdefs.h>
#include <QLine>
#include <QPainterPath>

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846264;
#endif
#ifndef M_PI_2
constexpr double M_PI_2 = 1.57079632679489661923132; // PI * 0.5
#endif
#ifndef M_2PI
constexpr double M_2PI = 6.28318530717958647692528;  // PI * 2
#endif
constexpr double ANGLE_15_RAD = 0.261799;	// 15度对应的弧度
constexpr double DELTA_DIST = 5.0;		// 较小的距离增量，通常用于移动时的判断
constexpr double DELTA_DIST_2 = 8.0;	// 较大的距离增量，通常用于点击时的判断

class xDef
{
	Q_GADGET

public:
	enum ActionStatus {
		S_Unknown = -1,
		S_Default = 0,
		S_DrawEntity1_P1,
		S_DrawEntity1_P2,
		S_DrawEntity1_P3,
		S_DrawEntity2_P1,
		S_DrawEntity2_P2,
		S_DrawEntity2_P3,
		S_DrawFinished,
		S_Measured,
		S_ActionFinished
	};
	Q_ENUM(ActionStatus)
	
	enum ActionType {
		AT_Unknown = -1,
		AT_Default = 0,
		AT_DrawLine,
		AT_DrawCircle,
		AT_DrawArc,
		AT_DrawPoint,
	};
	Q_ENUM(ActionType)

	xDef() = delete;
	~xDef() = delete;
	Q_DISABLE_COPY_MOVE(xDef)
};

/**
 * @brief 根据基础Path创建具有宽度的空心Path
 * @param path 传入的绘画路径
 * @param width 传入的宽度
 * @return 创建具有宽度的路径
*/
QPainterPath StrokeShapeFromPath(const QPainterPath &path, qreal width);

/**
 * @brief 通过极坐标生成点
 * @param length 长度
 * @param angle 角度，单位为弧度
 * @return 生成的点
*/
constexpr inline QPointF PointFromPolar(qreal length, qreal angle)
{
	return QPointF(std::cos(angle) * length, -std::sin(angle) * length);
}

/**
 * @brief 计算两点间的距离
*/
inline double Distance(const QPointF &p1, const QPointF &p2)
{
	return hypot(p2.x() - p1.x(), p2.y() - p1.y());
}

/**
 * @brief 点到直线的距离
*/
double DistancePoint2Line(const QPointF &p, const QLineF &line);

/**
 * @brief 计算p1到p2形成的倾斜角（弧度）
*/
double AnglePoint2Point(const QPointF &p1, const QPointF &p2);

/**
 * @brief 由圆心、半径及3个控制点组成的圆
*/
struct xCircleData
{
	explicit xCircleData() = default;
	xCircleData(const QPointF &center, qreal radius);
	xCircleData(qreal cx, qreal cy, qreal radius);
	xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	constexpr QPointF center() const { return c; }
	void setCenter(const QPointF &center);
	constexpr qreal radius() const { return r; }
	void setRadius(qreal radius);
	constexpr QPointF pt1() const { return p1; }
	constexpr QPointF pt2() const { return p2; }
	constexpr QPointF pt3() const { return p3; }
	inline void translate(const QPointF &p);

	inline bool isNull() const;
	friend constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2);

private:
	// 由3点构造圆心和半径
	void createFrom3P();
	// 由圆心半径构造3点（0°，120°，240°）
	void generate3P();

	QPointF c;
	qreal r = 0.0;
	QPointF p1, p2, p3;
};

inline void xCircleData::translate(const QPointF &p)
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

inline bool xCircleData::isNull() const
{
	return (c.isNull() || r <= 0.00001);
}

constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2)
{
	return (c1.c == c2.c && qFuzzyCompare(c1.r, c2.r));
}
