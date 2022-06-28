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
			brush->setStyle(Qt::NoBrush);
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
			pen->setColor(Qt::yellow);
			pen->setWidthF(2.0 / factor);
		}
		break;
	case xDef::Style::S_TxtHovered:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(255, 105, 0, 200));
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

QPainterPath StrokeShapeFromPath(const QPainterPath &path, qreal width)
{
	if (path.isEmpty() || width < 0.001)
		return path;

	QPainterPathStroker ps;
	ps.setCapStyle(Qt::FlatCap);
	ps.setJoinStyle(Qt::BevelJoin);
	ps.setWidth(width);
	return ps.createStroke(path);
}

double DistancePoint2Line(const QPointF &p, const QLineF &line)
{
	const auto v1 = p - line.p1();
	const auto v2 = line.p2() - line.p1();
	const double S = v1.x() * v2.y() - v1.y() * v2.x();
	const double l = line.length();
	if (l > 0.000001)
		return fabs(S / l);
	return -1.0;
}

double AnglePoint2Point(const QPointF &p1, const QPointF &p2)
{
	const qreal dx = p2.x() - p1.x();
	const qreal dy = p2.y() - p1.y();

	const qreal theta = std::atan2(-dy, dx);

	const qreal theta_normalized = theta < 0 ? theta + M_2PI : theta;

	if (qFuzzyCompare(theta_normalized, M_2PI))
		return 0.0;
	else
		return theta_normalized;
}
