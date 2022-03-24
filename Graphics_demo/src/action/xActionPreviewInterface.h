#pragma once

#include "xActionInterface.h"

/**
 * @brief ActionÔ¤ÀÀ²ã½Ó¿Ú
*/
class xActionPreviewInterface : public xActionInterface
{
public:
	xActionPreviewInterface(xGraphicView *view, xDef::ActionType type);
	~xActionPreviewInterface();

	virtual void confirm();
	virtual void cancel() = 0;
	virtual bool isFinished() const;

};
