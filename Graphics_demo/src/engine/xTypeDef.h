#pragma once

#include <qobjectdefs.h>
#include <QLine>
#include <QPainterPath>
#include <QDebug>
#include "xUtils.h"

/**
 * @brief Definitions about Entity
*/
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
		AT_DrawInterArc,
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
 * @brief 设置相应Style的样式
 * @param style 样式枚举
 * @param pen 传入的画笔指针
 * @param brush 传入的笔刷指针
 * @param factor 视图的缩放系数，用于设置画笔宽度
*/
void MakeStyle(xDef::Style style = xDef::S_NoStyle, QPen *pen = nullptr, QBrush *brush = nullptr, qreal factor = 1.0);

/**
 * @brief 由圆心、半径及3个控制点组成的圆
*/
struct xCircleData
{
	xCircleData() noexcept {}
	xCircleData(const xCircleData &other) noexcept = default;
	xCircleData(xCircleData &&other) noexcept = default;
	inline xCircleData(const QPointF &center, qreal radius) noexcept;
	inline xCircleData(qreal cx, qreal cy, qreal radius) noexcept;
	inline xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept;

	QPointF center() const noexcept { return c; }
	inline void setCenter(const QPointF &center) noexcept;
	qreal radius() const noexcept { return r; }
	inline void setRadius(qreal radius) noexcept;
	QPointF pt1() const noexcept { return p1; }
	QPointF pt2() const noexcept { return p2; }
	QPointF pt3() const noexcept { return p3; }
	// 圆的外接矩形
	QRectF boundingRect() const noexcept { return QRectF(c.x() - r, c.y() - r, r * 2, r * 2); }
	inline void translate(const QPointF &p) noexcept;

	inline bool isValid() const noexcept;
	friend inline bool operator==(const xCircleData &c1, const xCircleData &c2) noexcept;
	xCircleData &operator=(const xCircleData &o) noexcept = default;
	xCircleData &operator=(xCircleData &&o) noexcept = default;

private:
	// 由3点构造圆心和半径
	void createFrom3P() noexcept;
	// 由圆心半径构造3点（0°，120°，240°）
	inline void generate3P() noexcept;

	QPointF c;
	qreal r = 0.0;
	QPointF p1, p2, p3;
};

/**
 * @brief 由圆心、半径、起始角度、扫过角度及3个控制点组成的圆弧
*/
struct xArcData
{
	xArcData() noexcept {}
	xArcData(const xArcData &other) noexcept = default;
	xArcData(xArcData &&other) noexcept = default;
	inline xArcData(const QPointF &center, qreal radius, qreal angle, qreal spanAngle) noexcept;
	inline xArcData(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept;

	QPointF center() const noexcept { return c; }
	inline void setCenter(const QPointF &center) noexcept;
	qreal radius() const noexcept { return r; }
	inline void setRadius(qreal radius) noexcept;
	// 起始角度（弧度）
	qreal angle() const noexcept { return a; }
	inline void setAngle(qreal angle) noexcept;
	// 经过的角度（弧度）
	qreal spanAngle() const noexcept { return sa; }
	inline void setSpanAngle(qreal alength) noexcept;
	// 起始角度（度）
	qreal angleDegree() const noexcept { return a * 180 / M_PI; }
	inline void setAngleDegree(qreal angle) noexcept;
	// 经过的角度（度）
	qreal spanAngleDegree() const noexcept { return sa * 180 / M_PI; }
	inline void setSpanAngleDegree(qreal alength) noexcept;
	QPointF pt1() const noexcept { return p1; }
	QPointF pt2() const noexcept { return p2; }
	QPointF pt3() const noexcept { return p3; }
	// 圆弧所在圆的外接矩形
	QRectF boundingRect() const noexcept { return QRectF(c.x() - r, c.y() - r, r * 2, r * 2); }
	inline void translate(const QPointF &p) noexcept;

	inline bool isValid() const noexcept;
	friend inline bool operator==(const xArcData &arc1, const xArcData &arc2) noexcept;
	xArcData &operator=(const xArcData &o) noexcept = default;
	xArcData &operator=(xArcData &&o) noexcept = default;

private:
	// 由3点构造圆心、半径及角度
	void createFrom3P() noexcept;
	// 由圆心半径与角度构造3个点
	inline void generate3P() noexcept;

	QPointF c;
	qreal r = 0.0;
	qreal a = 0.0;		// 起始角度（弧度）
	qreal sa = 0.0;	// 扫过角度（弧度），逆时针为正，顺时针为负
	QPointF p1, p2, p3;
};

// 将圆弧转换为近似逼近的多边形
QPolygonF ArcToPolygon(const xArcData &arc);

// 将圆弧转换为近似逼近的多边形
QPolygonF ArcToPolygon(const QPointF &center, qreal radius, qreal angle, qreal spanAngle);

// struct xCircleData
inline xCircleData::xCircleData(const QPointF &c, qreal r) noexcept
	: c(c)
	, r(r)
{
	generate3P();
}

inline xCircleData::xCircleData(qreal cx, qreal cy, qreal r) noexcept
	: c(cx, cy)
	, r(r)
{
	generate3P();
}

inline xCircleData::xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept
	: p1(p1), p2(p2), p3(p3)
{
	createFrom3P();
}

inline void xCircleData::setCenter(const QPointF &center) noexcept
{
	if (center == c)
		return;
	auto d = center - c;
	p1 += d;
	p2 += d;
	p3 += d;
	c = center;
}

inline void xCircleData::setRadius(qreal radius) noexcept
{
	if (qFuzzyCompare(radius, r))
		return;

	r = radius;
	p1 = c + PointFromPolar(r, QLineF(c, p1).angle() * M_PI / 180.0);
	p2 = c + PointFromPolar(r, QLineF(c, p2).angle() * M_PI / 180.0);
	p3 = c + PointFromPolar(r, QLineF(c, p3).angle() * M_PI / 180.0);
}

inline void xCircleData::generate3P() noexcept
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

inline void xCircleData::translate(const QPointF &p) noexcept
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

inline bool xCircleData::isValid() const noexcept
{
	return (r > 0.00001);
}

inline bool operator==(const xCircleData &c1, const xCircleData &c2) noexcept
{
	return (c1.c == c2.c && qFuzzyCompare(c1.r, c2.r));
}

// struct xArcData
inline xArcData::xArcData(const QPointF &center, qreal radius, qreal angle, qreal spanAngle) noexcept
	: c(center)
	, r(radius)
	, a(angle)
	, sa(spanAngle)
{
	while (a < 0)
	{
		a += M_2PI;
	}
	while (a > M_2PI)
	{
		a -= M_2PI;
	}
	while (sa < -M_2PI)
	{
		sa += M_2PI;
	}
	while (sa > M_2PI)
	{
		sa -= M_2PI;
	}
	generate3P();
}

inline xArcData::xArcData(const QPointF &p1, const QPointF &p2, const QPointF &p3) noexcept
	: p1(p1), p2(p2), p3(p3)
{
	createFrom3P();
}

inline void xArcData::generate3P() noexcept
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

inline void xArcData::setCenter(const QPointF &center) noexcept
{
	if (center == c)
		return;
	auto d = center - c;
	p1 += d;
	p2 += d;
	p3 += d;
	c = center;
}

inline void xArcData::setRadius(qreal radius) noexcept
{
	if (qFuzzyCompare(radius, r))
		return;

	r = radius;
	p1 = c + PointFromPolar(r, QLineF(c, p1).angle() * M_PI / 180.0);
	p2 = c + PointFromPolar(r, QLineF(c, p2).angle() * M_PI / 180.0);
	p3 = c + PointFromPolar(r, QLineF(c, p3).angle() * M_PI / 180.0);
}

inline void xArcData::setAngle(qreal angle) noexcept
{
	while (angle < 0)
	{
		angle += M_2PI;
	}
	while (angle > M_2PI)
	{
		angle -= M_2PI;
	}

	if (qFuzzyCompare(angle, a))
		return;

	a = angle;
	generate3P();
}

inline void xArcData::setSpanAngle(qreal alength) noexcept
{
	while (alength < -M_2PI)
	{
		alength += M_2PI;
	}
	while (alength > M_2PI)
	{
		alength -= M_2PI;
	}

	if (qFuzzyCompare(alength, sa))
		return;

	sa = alength;
	generate3P();
}

inline void xArcData::setAngleDegree(qreal angle) noexcept
{
	qreal arad = angle * M_PI / 180;
	while (arad < 0)
	{
		arad += M_2PI;
	}
	while (arad > M_2PI)
	{
		arad -= M_2PI;
	}

	if (qFuzzyCompare(arad, a))
		return;

	a = arad;
	generate3P();
}

inline void xArcData::setSpanAngleDegree(qreal alength) noexcept
{
	qreal arad = alength * M_PI / 180;
	while (arad < -M_2PI)
	{
		arad += M_2PI;
	}
	while (arad > M_2PI)
	{
		arad -= M_2PI;
	}

	if (qFuzzyCompare(arad, a))
		return;

	sa = arad;
	generate3P();
}

inline void xArcData::translate(const QPointF &p) noexcept
{
	c += p;
	p1 += p;
	p2 += p;
	p3 += p;
}

inline bool xArcData::isValid() const noexcept
{
	return (r > 0.00001 && fabs(sa) > 0.001);
}

inline bool operator==(const xArcData &arc1, const xArcData &arc2) noexcept
{
	return (arc1.c == arc2.c && qFuzzyCompare(arc1.r, arc2.r)
		&& qFuzzyCompare(arc1.a, arc2.a) && qFuzzyCompare(arc1.sa, arc2.sa));
}
