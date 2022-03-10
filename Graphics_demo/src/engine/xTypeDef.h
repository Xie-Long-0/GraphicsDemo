#pragma once

#include <qobjectdefs.h>
#include <QGraphicsItem>

constexpr double M_PI = 3.14159265358979323846264;

class xTypeDef
{

};

class xDef
{
	Q_GADGET

public:
	enum {
		ET_Line = QGraphicsItem::UserType + 1,
		ET_Circle,
		ET_Arc,
		ET_Point,
		ET_RegLine,
		ET_RegCircle,
		ET_RegArc,
		ET_RegPoint,
	};

	enum ActionStatus {
		S_Unknown = -1,
		S_Default = 0,
		S_DrawEntity1_Start = 1,
		S_DrawEntity1_P2,
		S_DrawEntity1_End,
		S_DrawEntity2_Start,
		S_DrawEntity2_P2,
		S_DrawEntity2_End,
		S_DrawFinished,
		S_Measured,
		S_ActionFinished
	};
	Q_ENUM(ActionStatus);
	
	enum ActionType {
		AT_Unknown = -1,
		AT_Default = 0,
		AT_DrawLine = 1,
		AT_DrawCircle,
		AT_DrawArc,
		AT_DrawPoint,
	};
	Q_ENUM(ActionType);

	xDef() = delete;
	~xDef() = delete;
	Q_DISABLE_COPY_MOVE(xDef)
};

/**
 * @brief 根据基础Path创建具有宽度的Path
 * @param path 传入的绘画路径
 * @param pen 传入的画笔
 * @return 根据pen的宽度创建的路径
*/
QPainterPath StrokeShapeFromPath(const QPainterPath &path, const QPen &pen);

/**
 * @brief 通过极坐标生成点
 * @param length 长度
 * @param angle 角度，单位为弧度
 * @return 生成的点
*/
inline QPointF PointFromPolar(qreal length, qreal angle);

/**
 * @brief 由圆心、半径及3个控制点组成的圆
*/
struct xCircleData
{
	explicit xCircleData() = default;
	xCircleData(const QPointF &center, qreal radius);
	xCircleData(qreal cx, qreal cy, qreal radius);
	xCircleData(const QPointF &p1, const QPointF &p2, const QPointF &p3);

	QPointF center() const { return c; }
	void setCenter(const QPointF &center);
	qreal radius() const { return r; }
	void setRadius(qreal radius);
	QPointF pt1() const { return p1; }
	QPointF pt2() const { return p2; }
	QPointF pt3() const { return p3; }

	bool isNull() const;
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

inline bool xCircleData::isNull() const
{
	return (c.isNull() || r <= 0.00001);
}

constexpr inline bool operator==(const xCircleData &c1, const xCircleData &c2)
{
	return (c1.c == c2.c && qFuzzyCompare(c1.r, c2.r));
}

inline QPointF PointFromPolar(qreal length, qreal angle)
{
	return QPointF(std::cos(angle) * length, -std::sin(angle) * length);
}
