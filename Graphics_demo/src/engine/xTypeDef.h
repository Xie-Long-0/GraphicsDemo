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
 * @brief ��Բ�ġ��뾶��3�����Ƶ���ɵ�Բ
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
	// Բ����Ӿ���
	QRectF boundingRect() const noexcept { return QRectF(c.x() - r, c.y() - r, r * 2, r * 2); }
	inline void translate(const QPointF &p) noexcept;

	inline bool isValid() const noexcept;
	friend inline bool operator==(const xCircleData &c1, const xCircleData &c2) noexcept;
	xCircleData &operator=(const xCircleData &o) noexcept = default;
	xCircleData &operator=(xCircleData &&o) noexcept = default;

private:
	// ��3�㹹��Բ�ĺͰ뾶
	void createFrom3P() noexcept;
	// ��Բ�İ뾶����3�㣨0�㣬120�㣬240�㣩
	inline void generate3P() noexcept;

	QPointF c;
	qreal r = 0.0;
	QPointF p1, p2, p3;
};

/**
 * @brief ��Բ�ġ��뾶����ʼ�Ƕȡ�ɨ���Ƕȼ�3�����Ƶ���ɵ�Բ��
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
	// ��ʼ�Ƕȣ����ȣ�
	qreal angle() const noexcept { return a; }
	inline void setAngle(qreal angle) noexcept;
	// �����ĽǶȣ����ȣ�
	qreal spanAngle() const noexcept { return sa; }
	inline void setSpanAngle(qreal alength) noexcept;
	// ��ʼ�Ƕȣ��ȣ�
	qreal angleDegree() const noexcept { return a * 180 / M_PI; }
	inline void setAngleDegree(qreal angle) noexcept;
	// �����ĽǶȣ��ȣ�
	qreal spanAngleDegree() const noexcept { return sa * 180 / M_PI; }
	inline void setSpanAngleDegree(qreal alength) noexcept;
	QPointF pt1() const noexcept { return p1; }
	QPointF pt2() const noexcept { return p2; }
	QPointF pt3() const noexcept { return p3; }
	// Բ������Բ����Ӿ���
	QRectF boundingRect() const noexcept { return QRectF(c.x() - r, c.y() - r, r * 2, r * 2); }
	inline void translate(const QPointF &p) noexcept;

	inline bool isValid() const noexcept;
	friend inline bool operator==(const xArcData &arc1, const xArcData &arc2) noexcept;
	xArcData &operator=(const xArcData &o) noexcept = default;
	xArcData &operator=(xArcData &&o) noexcept = default;

private:
	// ��3�㹹��Բ�ġ��뾶���Ƕ�
	void createFrom3P() noexcept;
	// ��Բ�İ뾶��Ƕȹ���3����
	inline void generate3P() noexcept;

	QPointF c;
	qreal r = 0.0;
	qreal a = 0.0;		// ��ʼ�Ƕȣ����ȣ�
	qreal sa = 0.0;	// ɨ���Ƕȣ����ȣ�����ʱ��Ϊ����˳ʱ��Ϊ��
	QPointF p1, p2, p3;
};

// ��Բ��ת��Ϊ���Ʊƽ��Ķ����
QPolygonF ArcToPolygon(const xArcData &arc);

// ��Բ��ת��Ϊ���Ʊƽ��Ķ����
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
