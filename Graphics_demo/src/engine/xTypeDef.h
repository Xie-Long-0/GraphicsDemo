#pragma once

#include <cmath>
#include <qobjectdefs.h>
#include <QLine>
#include <QPainterPath>
#include <QDebug>

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
		AS_Unknown = -1,
		AS_Default = 0,
		AS_DrawEntity1_P1,
		AS_DrawEntity1_P2,
		AS_DrawEntity1_P3,
		AS_DrawEntity2_P1,
		AS_DrawEntity2_P2,
		AS_DrawEntity2_P3,
		AS_DrawFinished,
		AS_Measured,
		AS_ActionFinished
	};
	Q_ENUM(ActionStatus)
	
	enum ActionType {
		AT_Unknown = -1,
		AT_Default = 0,
		AT_DrawLine,
		AT_DrawCircle,
		AT_DrawArc,
		AT_DrawPoint,
		AT_DrawRegLine,
		AT_DrawRegCircle,
		AT_DrawRegArc,
		AT_DrawRegPoint,
		AT_DrawRegRect,
		AT_DrawInterCircle,
	};
	Q_ENUM(ActionType)

	enum Style
	{
		S_NoStyle = 0,

		// ������Χʵ����ʽ
		S_Drawing = 10,   // ���ڻ�
		S_Drawn,          // �ѻ���
		S_Measured,       // �Ѳ���
		S_Failed,         // ʶ��ʧ��
		S_Selected,       // ѡ��
		S_Hovered,        // ��ͣ
		S_HoverSelected,

		// ����Χʵ����ʽ
		S_RegDrawing = 20,// ���ڻ�
		S_RegDrawn,       // �ѻ���
		S_RegMeasured,    // �Ѳ���
		S_RegFailed,      // ʶ��ʧ��
		S_RegSelected,    // ѡ��
		S_RegHovered,     // ��ͣ
		S_RegHoverSelected,

		// ������ʽ
		S_TxtDrawing = 30,// ���ڻ�
		S_TxtDrawn,       // �ѻ���
		S_TxtMeasured,    // �Ѳ���
		S_TxtFailed,      // ʶ��ʧ��
		S_TxtSelected,    // ѡ��
		S_TxtHovered,     // ��ͣ
	};
	Q_ENUM(Style)

	enum EntityStatus
	{
		ES_NotMeasured,
		ES_MeasureOK,
		ES_MeasureFailed,
	};
	Q_ENUM(EntityStatus)

	xDef() = delete;
	~xDef() = delete;
	Q_DISABLE_COPY_MOVE(xDef)
};

/**
 * @brief ������ӦStyle����ʽ
 * @param style ��ʽö��
 * @param pen ����Ļ���ָ��
 * @param brush ����ı�ˢָ��
 * @param factor ��ͼ������ϵ�����������û��ʿ��
*/
void MakeStyle(xDef::Style style = xDef::S_NoStyle, QPen *pen = nullptr, QBrush *brush = nullptr, qreal factor = 1.0);

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
 * @brief ����p1��p2�γɵ���б�ǣ����ȣ���[0, 2PI)
*/
double AnglePoint2Point(const QPointF &p1, const QPointF &p2);

/**
 * @brief ��Բ�ġ��뾶��3�����Ƶ���ɵ�Բ
*/
struct xCircleData
{
	constexpr xCircleData() = default;
	constexpr xCircleData(const xCircleData &other) noexcept = default;
	constexpr xCircleData(xCircleData &&other) noexcept = default;
	constexpr xCircleData(const QPointF &center, qreal radius);
	constexpr xCircleData(qreal cx, qreal cy, qreal radius);
	constexpr xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	constexpr QPointF center() const noexcept { return c; }
	constexpr inline void setCenter(const QPointF &center) noexcept;
	constexpr qreal radius() const noexcept { return r; }
	constexpr inline void setRadius(qreal radius);
	constexpr QPointF pt1() const noexcept { return p1; }
	constexpr QPointF pt2() const noexcept { return p2; }
	constexpr QPointF pt3() const noexcept { return p3; }
	constexpr inline void translate(const QPointF &p) noexcept;

	constexpr inline bool isValid() const noexcept;
	friend constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2) noexcept;
	constexpr xCircleData &operator=(const xCircleData &o) noexcept = default;
	constexpr xCircleData &operator=(xCircleData &&o) noexcept = default;

private:
	// ��3�㹹��Բ�ĺͰ뾶
	constexpr inline void createFrom3P();
	// ��Բ�İ뾶����3�㣨0�㣬120�㣬240�㣩
	constexpr inline void generate3P();

	QPointF c;
	qreal r = 0.0;
	QPointF p1, p2, p3;
};

/**
 * @brief ��Բ�ġ��뾶����ʼ�Ƕȡ�ɨ���Ƕȼ�3�����Ƶ���ɵ�Բ��
*/
struct xArcData
{
	constexpr xArcData() = default;
	constexpr xArcData(const xArcData &other) noexcept = default;
	constexpr xArcData(xArcData &&other) noexcept = default;
	constexpr xArcData(const QPointF &center, qreal radius, qreal angle, qreal spanAngle);
	constexpr xArcData(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	constexpr QPointF center() const noexcept { return c; }
	constexpr inline void setCenter(const QPointF &center) noexcept;
	constexpr qreal radius() const noexcept { return r; }
	constexpr inline void setRadius(qreal radius);
	constexpr qreal startAngle() const noexcept { return a; }
	constexpr inline void setStartAngle(qreal angle);
	constexpr qreal spanAngle() const noexcept { return sa; }
	constexpr inline void setAngleLength(qreal alength);
	constexpr QPointF pt1() const noexcept { return p1; }
	constexpr QPointF pt2() const noexcept { return p2; }
	constexpr QPointF pt3() const noexcept { return p3; }
	constexpr inline void translate(const QPointF &p) noexcept;

	constexpr inline bool isValid() const noexcept;
	friend constexpr inline bool operator==(const xArcData &arc1, const xArcData &arc2) noexcept;
	constexpr xArcData &operator=(const xArcData &o) noexcept = default;
	constexpr xArcData &operator=(xArcData &&o) noexcept = default;

private:
	// ��3�㹹��Բ�ġ��뾶���Ƕ�
	constexpr inline void createFrom3P();
	// ��Բ�İ뾶��Ƕȹ���3����
	constexpr inline void generate3P();

	QPointF c;
	qreal r = 0.0;
	qreal a = 0.0;		// ��ʼ�Ƕȣ����ȣ�
	qreal sa = 0.0;	// ɨ���Ƕȣ����ȣ�����ʱ��Ϊ����˳ʱ��Ϊ��
	QPointF p1, p2, p3;
};

// struct xCircleData
constexpr inline xCircleData::xCircleData(const QPointF &c, qreal r)
	: c(c)
	, r(r)
{
	generate3P();
}

constexpr inline xCircleData::xCircleData(qreal cx, qreal cy, qreal r)
	: c(cx, cy)
	, r(r)
{
	generate3P();
}

constexpr inline xCircleData::xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3)
	: p1(p1), p2(p2), p3(p3)
{
	createFrom3P();
}

constexpr inline void xCircleData::setCenter(const QPointF &center) noexcept
{
	if (center == c)
		return;
	auto d = center - c;
	p1 += d;
	p2 += d;
	p3 += d;
	c = center;
}

constexpr inline void xCircleData::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, r))
		return;

	r = radius;
	p1 = c + PointFromPolar(r, QLineF(c, p1).angle() * M_PI / 180.0);
	p2 = c + PointFromPolar(r, QLineF(c, p2).angle() * M_PI / 180.0);
	p3 = c + PointFromPolar(r, QLineF(c, p3).angle() * M_PI / 180.0);
}

constexpr inline void xCircleData::createFrom3P()
{
	if (p1 == p2 || p2 == p3 || p3 == p1)
	{
		qWarning() << __FUNCTION__ << ": There are some points invalid";
		return;
	}

	const auto va = p2 - p1;
	const auto vb = p3 - p1;
	const qreal ra2 = QPointF::dotProduct(va, va) * 0.5;
	const qreal rb2 = QPointF::dotProduct(vb, vb) * 0.5;
	const qreal crossp = va.x() * vb.y() - va.y() * vb.x();
	// crosspΪ0��3����ͬһֱ����
	if (qFuzzyCompare(crossp, 0.0))
	{
		qWarning() << __FUNCTION__ << ": Three points in a line";
		c = QPointF();
		r = 0;
		return;
	}
	c.setX((ra2 * vb.y() - rb2 * va.y()) / crossp);
	c.setY((rb2 * va.x() - ra2 * vb.x()) / crossp);
	r = QLineF(c, QPointF(0, 0)).length();
	c += p1;
}

constexpr inline void xCircleData::generate3P()
{
	if (r < 0.00001)
	{
		qWarning() << __FUNCTION__ << ": The radius is invalid";
		return;
	}

	p1 = c + PointFromPolar(r, 0);
	p2 = c + PointFromPolar(r, M_PI * 2.0 / 3.0);
	p3 = c + PointFromPolar(r, M_PI * 4.0 / 3.0);
}

constexpr inline void xCircleData::translate(const QPointF &p) noexcept
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

constexpr inline bool xCircleData::isValid() const noexcept
{
	return (r > 0.00001);
}

constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2) noexcept
{
	return (c1.c == c2.c && qFuzzyCompare(c1.r, c2.r));
}

// struct xArcData
inline constexpr xArcData::xArcData(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
	: c(center)
	, r(radius)
	, a(angle)
	, sa(spanAngle)
{
	generate3P();
}

inline constexpr xArcData::xArcData(const QPointF &p1, const QPointF &p2, const QPointF &p3)
	: p1(p1), p2(p2), p3(p3)
{
	createFrom3P();
}

inline constexpr void xArcData::createFrom3P()
{
	auto p12 = p2 - p1;
	auto p23 = p3 - p2;
	auto p13 = p3 - p1;

	// p1 * p1
	qreal dp1 = QPointF::dotProduct(p1, p1);
	// p2 * p2 - p1 * p1
	qreal dp12 = QPointF::dotProduct(p2, p2) - dp1;
	// p3 * p3 - p1 * p1
	qreal dp13 = QPointF::dotProduct(p3, p3) - dp1;
	// cross-product, p12 x p23
	qreal cp12p23 = p12.x() * p23.y() - p12.y() * p23.x();
	// cross-product, p12 x p13
	qreal cp12p13 = p12.x() * p13.y() - p12.y() * p13.x();
	
	// 3�㹲��
	if (qFuzzyCompare(cp12p13, 0))
	{
		qWarning() << __FUNCTION__ << "Cannot create a Arc, 3 points on a line!";
		return;
	}

	qreal x0 = (p13.y() * dp12 - p12.y() * dp13) / (cp12p13 * 2);
	qreal y0 = (p12.x() * dp13 - p13.x() * dp12) / (cp12p13 * 2);

	// Բ��
	c = QPointF(x0, y0);
	// �뾶
	r = QLineF(c, p1).length();

	qreal a1 = AnglePoint2Point(c, p1);
	qreal a2 = AnglePoint2Point(c, p2);
	qreal a3 = AnglePoint2Point(c, p3);
	// ��ʼ�Ƕ�
	a = a1;
	// �ж�ɨ���ĽǶ�
	if (a1 > a3)
	{
		if (a2 < a1 && a2 > a3)
			sa = -(a1 - a3);
		else
			sa = M_2PI - (a1 - a3);
	}
	else
	{
		if (a2 < a3 && a2 > a1)
			sa = a3 - a1;
		else
			sa = a3 - a1 - M_2PI;
	}
}

inline constexpr void xArcData::generate3P()
{
	if (!isValid())
	{
		qWarning() << __FUNCTION__ << ": The radius is invalid";
		return;
	}

	p1 = c + PointFromPolar(r, a);
	p2 = c + PointFromPolar(r, a + sa * 0.5);
	p3 = c + PointFromPolar(r, a + sa);
}

inline constexpr void xArcData::setCenter(const QPointF &center) noexcept
{
	if (center == c)
		return;
	auto d = center - c;
	p1 += d;
	p2 += d;
	p3 += d;
	c = center;
}

inline constexpr void xArcData::setRadius(qreal radius)
{
	if (qFuzzyCompare(radius, r))
		return;

	r = radius;
	p1 = c + PointFromPolar(r, QLineF(c, p1).angle() * M_PI / 180.0);
	p2 = c + PointFromPolar(r, QLineF(c, p2).angle() * M_PI / 180.0);
	p3 = c + PointFromPolar(r, QLineF(c, p3).angle() * M_PI / 180.0);
}

inline constexpr void xArcData::setStartAngle(qreal angle)
{
	if (qFuzzyCompare(angle, a))
		return;

	a = angle;
	generate3P();
}

inline constexpr void xArcData::setAngleLength(qreal alength)
{
	if (qFuzzyCompare(alength, sa))
		return;

	sa = alength;
	generate3P();
}

inline constexpr void xArcData::translate(const QPointF &p) noexcept
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

inline constexpr bool xArcData::isValid() const noexcept
{
	return (r > 0.00001 && fabs(sa) > 0.001);
}

inline constexpr bool operator==(const xArcData &arc1, const xArcData &arc2) noexcept
{
	return (arc1.c == arc2.c && qFuzzyCompare(arc1.r, arc2.r)
		&& qFuzzyCompare(arc1.a, arc2.a) && qFuzzyCompare(arc1.sa, arc2.sa));
}
