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
			pen->setWidthF(2.0 / factor);
		}
		break;
	case xStyle::Failed:
		if (pen)
		{
			pen->setStyle(Qt::SolidLine);
			pen->setColor(Qt::red);
			pen->setWidthF(2.0 / factor);
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
		break;
	case xStyle::RegDrawn:
		break;
	case xStyle::RegMeasured:
		break;
	case xStyle::RegFailed:
		break;
	case xStyle::RegSelected:
		break;
	case xStyle::RegHovered:
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
