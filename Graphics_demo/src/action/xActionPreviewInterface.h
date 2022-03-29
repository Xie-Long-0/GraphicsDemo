#pragma once

#include "xActionInterface.h"

/**
 * @brief ActionԤ����ӿڣ��ṩȷ����ȡ���Ĳ���
*/
class xActionPreviewInterface : public xActionInterface
{
public:
	xActionPreviewInterface(xGraphicView *view, xDef::ActionType type);
	virtual ~xActionPreviewInterface();

	// ȷ����ɵ�ǰ����
	virtual void confirm();
	// ȡ����ǰ�Ĳ�������Ҫ�����������ʵ��
	virtual void cancel() = 0;
	// ��ǰ�����Ƿ�����ɣ�Ĭ������Ϊ�ж�(m_status >= xDef::S_ActionFinished)
	virtual bool isFinished() const;
};
