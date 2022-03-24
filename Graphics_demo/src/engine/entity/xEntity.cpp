#include "xEntity.h"
#include "xGraphicView.h"

xEntity::xEntity(xGraphicView *view)
	: m_view(view)
{
}

qreal xEntity::viewScaleFactor() const
{
	// 通过view的转换矩阵获取缩放系数
	return m_view->transform().m11();
}
