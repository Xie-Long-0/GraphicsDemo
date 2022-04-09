#pragma once

#include "xInterCoupleEntity.h"

class xInterLineAndLine : public xInterCoupleEntity
{
	Q_OBJECT

public:
	xInterLineAndLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	~xInterLineAndLine();

};
