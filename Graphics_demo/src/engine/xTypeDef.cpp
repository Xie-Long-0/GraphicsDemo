#include "xTypeDef.h"
#include <QPen>
#include <QDebug>

void MakeStyle(xDef::Style style, QPen *pen, QBrush *brush, qreal factor)
{
	switch (style)
	{
		// 不带范围实体样式
	case xDef::Style::S_Drawing:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(255, 105, 0, 255));
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xDef::Style::S_Drawn:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::cyan);
			pen->setWidthF(2.0 / factor);
		}
		break;

	case xDef::Style::S_Measured:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::green);
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xDef::Style::S_Failed:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::red);
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xDef::Style::S_Selected:
		if (pen)
		{
			pen->setStyle(Qt::DashDotLine);
			pen->setColor(QColor(255, 105, 0, 255));
			pen->setWidthF(3.0 / factor);
		}
		break;

	case xDef::Style::S_Hovered:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(3.0 / factor);
		}
		break;

	case xDef::Style::S_HoverSelected:
		if (pen)
		{
			pen->setStyle(Qt::DashDotLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(3.0 / factor);
		}
		break;

		// 带范围实体样式
	case xDef::Style::S_RegDrawing:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(255, 105, 0, 200));
			pen->setWidthF(2.0 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(255, 105, 0, 80));
		}
		break;

	case xDef::Style::S_RegDrawn:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::cyan);
			pen->setWidthF(2.0 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(0, 200, 180, 60));
		}
		break;

	case xDef::Style::S_RegMeasured:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::green);
			pen->setWidthF(2.5 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(0, 200, 180, 60));
		}
		break;

	case xDef::Style::S_RegFailed:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::red);
			pen->setWidthF(2.5 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::NoBrush);
		}
		break;

	case xDef::Style::S_RegSelected:
		if (pen)
		{
			pen->setStyle(Qt::DashDotLine);
			pen->setColor(QColor(255, 105, 0, 255));
			pen->setWidthF(3.0 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(255, 105, 0, 100));
		}
		break;

	case xDef::Style::S_RegHovered:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(3.0 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(255, 255, 0, 100));
		}
		break;

		// 文字样式
	case xDef::Style::S_TxtDrawing:
	case xDef::Style::S_TxtDrawn:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::cyan);
			pen->setWidthF(1.5 / factor);
		}
		break;
	case xDef::Style::S_TxtMeasured:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::green);
			pen->setWidthF(1.75 / factor);
		}
		break;
	case xDef::Style::S_TxtFailed:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::red);
			pen->setWidthF(1.75 / factor);
		}
		break;
	case xDef::Style::S_TxtSelected:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(255, 105, 0, 200));
			pen->setWidthF(2.0 / factor);
		}
		break;
	case xDef::Style::S_TxtHovered:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(2.0 / factor);
		}
		break;

	case xDef::Style::S_NoStyle:
	default:
		if (pen)
		{
			pen->setStyle(Qt::NoPen);
		}
		if (brush)
		{
			brush->setStyle(Qt::NoBrush);
		}
		break;
	}
}

QPolygonF ArcToPolygon(const xArcData &arc)
{
	const qreal da = (arc.spanAngle() > 0) ? 0.01 : -0.01;
	const qreal ea = arc.angle() + arc.spanAngle();
	QPolygonF pg;
	for (qreal a = arc.angle(); da > 0 ? (a < ea) : (a > ea); a += da)
	{
		auto p = arc.center() + PointFromPolar(arc.radius(), a);
		pg.append(std::move(p));
	}
	// 添加结束点
	auto pe = arc.center() + PointFromPolar(arc.radius(), ea);
	pg.append(std::move(pe));
	return pg;
}

QPolygonF ArcToPolygon(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
{
	const qreal da = (spanAngle > 0) ? 0.01 : -0.01;
	const qreal ea = angle + spanAngle;
	QPolygonF pg;
	for (qreal a = angle; da > 0 ? (a < ea) : (a > ea); a += da)
	{
		auto p = center + PointFromPolar(radius, a);
		pg.append(std::move(p));
	}
	// 添加结束点
	auto pe = center + PointFromPolar(radius, ea);
	pg.append(std::move(pe));
	return pg;
}

void xCircleData::createFrom3P()
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

xArcData::xArcData(const QPointF &center, qreal radius, qreal angle, qreal spanAngle)
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

void xArcData::createFrom3P()
{
	const auto p12 = p2 - p1;
	const auto p23 = p3 - p2;
	const auto p13 = p3 - p1;

	// p1 * p1
	const qreal dp1 = QPointF::dotProduct(p1, p1);
	// p2 * p2 - p1 * p1
	const qreal dp12 = QPointF::dotProduct(p2, p2) - dp1;
	// p3 * p3 - p1 * p1
	const qreal dp13 = QPointF::dotProduct(p3, p3) - dp1;
	// cross-product, p12 x p23
	const qreal cp12p23 = p12.x() * p23.y() - p12.y() * p23.x();
	// cross-product, p12 x p13
	const qreal cp12p13 = p12.x() * p13.y() - p12.y() * p13.x();

	// 3点共线
	if (qFuzzyCompare(cp12p13, 0))
	{
		qWarning() << __FUNCTION__ << "Cannot create a Arc, 3 points on a line!";
		return;
	}

	const qreal x0 = (p13.y() * dp12 - p12.y() * dp13) / (cp12p13 * 2);
	const qreal y0 = (p12.x() * dp13 - p13.x() * dp12) / (cp12p13 * 2);

	// 圆心
	c = QPointF(x0, y0);
	// 半径
	r = QLineF(c, p1).length();

	const qreal a1 = AnglePoint2Point(c, p1);
	const qreal a2 = AnglePoint2Point(c, p2);
	const qreal a3 = AnglePoint2Point(c, p3);
	// 起始角度
	a = a1;
	// 判断扫过的角度
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

void xArcData::setAngle(qreal angle)
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

void xArcData::setSpanAngle(qreal alength)
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

void xArcData::setAngleDegree(qreal angle)
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

void xArcData::setSpanAngleDegree(qreal alength)
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
