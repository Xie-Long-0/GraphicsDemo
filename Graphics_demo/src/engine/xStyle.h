#pragma once

#include <qobjectdefs.h>
#include <QPen>

/**
 * @brief 通过枚举快速设置相应样式
*/
class xStyle
{
	Q_GADGET
public:
	enum Style
	{
        NoStyle = 0,

        // 不带范围实体样式
        Drawing = 10,   // 正在画
        Drawn,          // 已画好
        Measured,       // 已测量
        Failed,         // 识别失败
        Selected,       // 选择
        Hovered,        // 悬停
        HoverSelected,

        // 带范围实体样式
        RegDrawing = 20,// 正在画
        RegDrawn,       // 已画好
        RegMeasured,    // 已测量
        RegFailed,      // 识别失败
        RegSelected,    // 选择
        RegHovered,     // 悬停
        RegHoverSelected,

        // 文字样式
        TxtDrawing = 30,// 正在画
        TxtDrawn,       // 已画好
        TxtMeasured,    // 已测量
        TxtFailed,      // 识别失败
        TxtSelected,    // 选择
        TxtHovered,     // 悬停
    };
    Q_ENUM(Style);

	/**
	 * @brief 设置相应Style的样式
	 * @param style 样式枚举
	 * @param pen 传入的画笔指针
	 * @param brush 传入的笔刷指针
	 * @param factor 视图的缩放系数，用于设置画笔宽度
	*/
	static void makeStyle(Style style = NoStyle, QPen *pen = nullptr, QBrush *brush = nullptr, qreal factor = 1.0);
    xStyle() = delete;
    ~xStyle() = delete;
    Q_DISABLE_COPY_MOVE(xStyle)
};
