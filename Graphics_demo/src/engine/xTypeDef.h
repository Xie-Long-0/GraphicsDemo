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
constexpr double ANGLE_15_RAD = 0.261799;	// 15�ȶ�Ӧ�Ļ���
constexpr double DELTA_DIST = 5.0;		// ��С�ľ���������ͨ�������ƶ�ʱ���ж�
constexpr double DELTA_DIST_2 = 8.0;	// �ϴ�ľ���������ͨ�����ڵ��ʱ���ж�

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
constexpr inline QPointF PointFromPolar(qreal length, qreal angle)
{
	return QPointF(std::cos(angle) * length, -std::sin(angle) * length);
}

/**
 * @brief ���������ľ���
*/
inline double Distance(const QPointF &p1, const QPointF &p2)
{
	return hypot(p2.x() - p1.x(), p2.y() - p1.y());
}

/**
 * @brief �㵽ֱ�ߵľ���
*/
double DistancePoint2Line(const QPointF &p, const QLineF &line);

/**
 * @brief ����p1��p2�γɵ���б�ǣ����ȣ�
*/
double AnglePoint2Point(const QPointF &p1, const QPointF &p2);

/**
 * @brief ��Բ�ġ��뾶��3�����Ƶ���ɵ�Բ
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
	// ��3�㹹��Բ�ĺͰ뾶
	void createFrom3P();
	// ��Բ�İ뾶����3�㣨0�㣬120�㣬240�㣩
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
