#pragma once

#include <qmath.h>
#include <qpainterpath.h>

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846264;
#define M_PI M_PI
#endif
#ifndef M_PI_2
constexpr double M_PI_2 = 1.57079632679489661923132; // PI * 0.5
#define M_PI_2 M_PI_2
#endif
#ifndef M_2PI
constexpr double M_2PI = 6.28318530717958647692528;  // PI * 2
#define M_2PI M_2PI
#endif
constexpr double ANGLE_15_RAD = 0.261799;	// 15度对应的弧度
constexpr double DELTA_DIST = 5.0;		// 较小的距离增量，通常用于移动时的判断
constexpr double DELTA_DIST_2 = 8.0;	// 较大的距离增量，通常用于点击时的判断

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
inline QPointF PointFromPolar(qreal length, qreal angle)
{
	return QPointF(std::cos(angle) * length, -std::sin(angle) * length);
}

/**
 * @brief 计算两点间的距离
*/
inline double Distance(const QPointF &p1, const QPointF &p2)
{
	return std::hypot(p2.x() - p1.x(), p2.y() - p1.y());
}

/**
 * @brief 点到直线的距离
*/
double DistancePoint2Line(const QPointF &p, const QLineF &line);

/**
 * @brief 计算p1到p2形成的倾斜角（弧度），[0, 2PI)
 * @param reverseY 指示Y轴坐标是否反转
 * @return p1到p2形成的倾斜角（弧度）
*/
double AnglePoint2Point(const QPointF &p1, const QPointF &p2, bool reverseY = true) noexcept;

/**
 * @brief 判断srcAngle是否在某个范围内
 * @param srcAngle 源角（弧度）
 * @param angle 起始角（弧度）
 * @param spanAngle 扫过角度（弧度）
*/
bool AngleIsBetween(double srcAngle, double angle, double spanAngle) noexcept;

/**
 * @brief 将角度转换到 [0, 2PI) 范围（弧度）
*/
constexpr double NormalizeAngle(double angle) noexcept
{
	if (qFuzzyCompare(angle, M_2PI))
		return 0.0;

	if (angle < 0)
		return NormalizeAngle(angle + M_2PI);
	else if (angle > M_2PI)
		return NormalizeAngle(angle - M_2PI);
	else
		return angle;
}

/**
 * @brief 将角度转换到 [0, 360) 范围
*/
constexpr double NormalizeAngleDegree(double angle) noexcept
{
	if (qFuzzyCompare(angle, 360.0))
		return 0.0;

	if (angle < 0)
		return NormalizeAngle(angle + 360);
	else if (angle > 360.0)
		return NormalizeAngle(angle - 360);
	else
		return angle;
}
