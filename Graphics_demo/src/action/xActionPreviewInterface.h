#pragma once

#include "xActionInterface.h"

/**
 * @brief Action预览层接口，提供确认与取消的操作
*/
class xActionPreviewInterface : public xActionInterface
{
public:
	xActionPreviewInterface(xGraphicView *view, xDef::ActionType type);
	virtual ~xActionPreviewInterface();

	// 确认完成当前操作
	virtual void confirm();
	// 取消当前的操作，需要由派生类具体实现
	virtual void cancel() = 0;
	// 当前操作是否已完成，默认条件为判断(m_status >= xDef::S_ActionFinished)
	virtual bool isFinished() const;
};
