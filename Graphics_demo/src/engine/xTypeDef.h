#pragma once

#include <qobjectdefs.h>
#include <QGraphicsItem>

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
		S_DrawEntity1_End,
		S_DrawEntity2_Start,
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

};