#include "xStyle.h"

void xStyle::makeStyle(Style style, QPen *pen, QBrush *brush, qreal factor)
{
	switch (style)
	{
		// 不带范围实体样式
	case xStyle::Drawing:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(255, 105, 0, 255));
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xStyle::Drawn:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::blue);
			pen->setWidthF(2.0 / factor);
		}
		break;

	case xStyle::Measured:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::green);
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xStyle::Failed:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::red);
			pen->setWidthF(2.5 / factor);
		}
		break;

	case xStyle::Selected:
		if (pen)
		{
			pen->setStyle(Qt::DashDotLine);
			pen->setColor(QColor(255, 105, 0, 255));
			pen->setWidthF(3.0 / factor);
		}
		break;

	case xStyle::Hovered:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(3.0 / factor);
		}
		break;

	case xStyle::HoverSelected:
		if (pen)
		{
			pen->setStyle(Qt::DashDotLine);
			pen->setColor(Qt::yellow);
			pen->setWidthF(3.0 / factor);
		}
		break;

		// 带范围实体样式
	case xStyle::RegDrawing:
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

	case xStyle::RegDrawn:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(QColor(0, 50, 225, 255));
			pen->setWidthF(2.0 / factor);
		}
		if (brush)
		{
			brush->setStyle(Qt::SolidPattern);
			brush->setColor(QColor(0, 50, 200, 80));
		}
		break;

	case xStyle::RegMeasured:
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

	case xStyle::RegFailed:
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

	case xStyle::RegSelected:
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

	case xStyle::RegHovered:
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
	case xStyle::TxtDrawing:
		break;
	case xStyle::TxtDrawn:
		break;
	case xStyle::TxtMeasured:
		break;
	case xStyle::TxtFailed:
		break;
	case xStyle::TxtSelected:
		break;
	case xStyle::TxtHovered:
		break;

	case xStyle::NoStyle:
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
