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
constexpr double ANGLE_15_RAD = 0.261799;	// 15�ȶ�Ӧ�Ļ���
constexpr double DELTA_DIST = 5.0;		// ��С�ľ���������ͨ�������ƶ�ʱ���ж�
constexpr double DELTA_DIST_2 = 8.0;	// �ϴ�ľ���������ͨ�����ڵ��ʱ���ж�

/**
 * @brief ���ݻ���Path�������п�ȵĿ���Path
 * @param path ����Ļ滭·��
 * @param width ����Ŀ��
 * @return �������п�ȵ�·��
*/
QPainterPath StrokeShapeFromPath(const QPainterPath &path, qreal width);

/**
 * @brief ͨ�����������ɵ�
 * @param length ����
 * @param angle �Ƕȣ���λΪ����
 * @return ���ɵĵ�
*/
inline QPointF PointFromPolar(qreal length, qreal angle)
{
	return QPointF(std::cos(angle) * length, -std::sin(angle) * length);
}

/**
 * @brief ���������ľ���
*/
inline double Distance(const QPointF &p1, const QPointF &p2)
{
	return std::hypot(p2.x() - p1.x(), p2.y() - p1.y());
}

/**
 * @brief �㵽ֱ�ߵľ���
*/
double DistancePoint2Line(const QPointF &p, const QLineF &line);

/**
 * @brief ����p1��p2�γɵ���б�ǣ����ȣ���[0, 2PI)
 * @param reverseY ָʾY�������Ƿ�ת
 * @return p1��p2�γɵ���б�ǣ����ȣ�
*/
double AnglePoint2Point(const QPointF &p1, const QPointF &p2, bool reverseY = true) noexcept;

/**
 * @brief �ж�srcAngle�Ƿ���ĳ����Χ��
 * @param srcAngle Դ�ǣ����ȣ�
 * @param angle ��ʼ�ǣ����ȣ�
 * @param spanAngle ɨ���Ƕȣ����ȣ�
*/
bool AngleIsBetween(double srcAngle, double angle, double spanAngle) noexcept;

/**
 * @brief ���Ƕ�ת���� [0, 2PI) ��Χ�����ȣ�
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
 * @brief ���Ƕ�ת���� [0, 360) ��Χ
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
