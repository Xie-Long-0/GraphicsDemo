#include "xEntity.h"
#include "xGraphicView.h"

xEntity::xEntity(xGraphicView *view)
	: m_view(view)
{
}

qreal xEntity::viewScaleFactor() const
{
	// ͨ��view��ת�������ȡ����ϵ��
	return m_view->transform().m11();
}
