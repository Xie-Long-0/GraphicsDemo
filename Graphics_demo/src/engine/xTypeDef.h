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
constexpr double ANGLE_15_RAD = 0.261799;	// 15度对应的弧度
constexpr double DELTA_DIST = 5.0;		// 较小的距离增量，通常用于移动时的判断
constexpr double DELTA_DIST_2 = 8.0;	// 较大的距离增量，通常用于点击时的判断

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
	};
	Q_ENUM(ActionType)

	enum Style
	{
		S_NoStyle = 0,

		// 不带范围实体样式
		S_Drawing = 10,   // 正在画
		S_Drawn,          // 已画好
		S_Measured,       // 已测量
		S_Failed,         // 识别失败
		S_Selected,       // 选择
		S_Hovered,        // 悬停
		S_HoverSelected,

		// 带范围实体样式
		S_RegDrawing = 20,// 正在画
		S_RegDrawn,       // 已画好
		S_RegMeasured,    // 已测量
		S_RegFailed,      // 识别失败
		S_RegSelected,    // 选择
		S_RegHovered,     // 悬停
		S_RegHoverSelected,

		// 文字样式
		S_TxtDrawing = 30,// 正在画
		S_TxtDrawn,       // 已画好
		S_TxtMeasured,    // 已测量
		S_TxtFailed,      // 识别失败
		S_TxtSelected,    // 选择
		S_TxtHovered,     // 悬停
	};
	Q_ENUM(Style)

	enum EntityStatus
	{
		ES_Init = 0,
		ES_Drawing,
		ES_Drawn,
		ES_Selected,
		ES_Hovered,
		ES_MeasureOK,
		ES_MeasureFailed,
	};
	Q_ENUM(EntityStatus)

	xDef() = delete;
	~xDef() = delete;
	Q_DISABLE_COPY_MOVE(xDef)
};

/**
 * @brief 设置相应Style的样式
 * @param style 样式枚举
 * @param pen 传入的画笔指针
 * @param brush 传入的笔刷指针
 * @param factor 视图的缩放系数，用于设置画笔宽度
*/
void MakeStyle(xDef::Style style = xDef::S_NoStyle, QPen *pen = nullptr, QBrush *brush = nullptr, qreal factor = 1.0);

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
	constexpr xCircleData() = default;
	constexpr xCircleData(const QPointF &center, qreal radius);
	constexpr xCircleData(qreal cx, qreal cy, qreal radius);
	constexpr xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	constexpr QPointF center() const { return c; }
	constexpr inline void setCenter(const QPointF &center);
	constexpr qreal radius() const { return r; }
	constexpr inline void setRadius(qreal radius);
	constexpr QPointF pt1() const { return p1; }
	constexpr QPointF pt2() const { return p2; }
	constexpr QPointF pt3() const { return p3; }
	constexpr inline void translate(const QPointF &p);

	constexpr inline bool isValid() const;
	friend constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2);

private:
	// 由3点构造圆心和半径
	constexpr inline void createFrom3P();
	// 由圆心半径构造3点（0°，120°，240°）
	constexpr inline void generate3P();

	QPointF c;
	qreal r = 0.0;
	QPointF p1, p2, p3;
};

// class xCircleData
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

constexpr inline void xCircleData::setCenter(const QPointF &center)
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
	// crossp为0则3点在同一直线上
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

constexpr inline void xCircleData::translate(const QPointF &p)
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

constexpr inline bool xCircleData::isValid() const
{
	return (r > 0.00001);
}

constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2)
{
	return (c1.c == c2.c && qFuzzyCompare(c1.r, c2.r));
}
