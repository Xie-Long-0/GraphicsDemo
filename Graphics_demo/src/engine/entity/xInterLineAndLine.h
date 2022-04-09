#pragma once

#include "xInterEntity.h"

class xInterLineAndLine : public xInterEntity
{
	Q_OBJECT

public:
	xInterLineAndLine(xGraphicView *view, QGraphicsItem *parent = nullptr);
	~xInterLineAndLine();

};
