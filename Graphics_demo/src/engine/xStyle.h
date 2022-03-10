#pragma once

#include <qobjectdefs.h>
#include <QPen>

/**
 * @brief ͨ��ö�ٿ���������Ӧ��ʽ
*/
class xStyle
{
	Q_GADGET
public:
	enum Style
	{
        NoStyle = 0,

        // ������Χʵ����ʽ
        Drawing = 10,   // ���ڻ�
        Drawn,          // �ѻ���
        Measured,       // �Ѳ���
        Failed,         // ʶ��ʧ��
        Selected,       // ѡ��
        Hovered,        // ��ͣ
        HoverSelected,

        // ����Χʵ����ʽ
        RegDrawing = 20,// ���ڻ�
        RegDrawn,       // �ѻ���
        RegMeasured,    // �Ѳ���
        RegFailed,      // ʶ��ʧ��
        RegSelected,    // ѡ��
        RegHovered,     // ��ͣ
        RegHoverSelected,

        // ������ʽ
        TxtDrawing = 30,// ���ڻ�
        TxtDrawn,       // �ѻ���
        TxtMeasured,    // �Ѳ���
        TxtFailed,      // ʶ��ʧ��
        TxtSelected,    // ѡ��
        TxtHovered,     // ��ͣ
    };
    Q_ENUM(Style);

	/**
	 * @brief ������ӦStyle����ʽ
	 * @param style ��ʽö��
	 * @param pen ����Ļ���ָ��
	 * @param brush ����ı�ˢָ��
	 * @param factor ��ͼ������ϵ�����������û��ʿ��
	*/
	static void makeStyle(Style style = NoStyle, QPen *pen = nullptr, QBrush *brush = nullptr, qreal factor = 1.0);
    xStyle() = delete;
    ~xStyle() = delete;
    Q_DISABLE_COPY_MOVE(xStyle)
};
