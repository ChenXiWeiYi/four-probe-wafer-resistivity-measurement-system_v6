#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Init_Style_Button
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Style_Button(void)
{
//    SetStyle_PushButton(ui->Button_SelSemiType);
//    SetStyle_PushButton(ui->Button_ControlVoltage);

//    SetStyle_ToolButton(ui->Button_CurrPos);
//    SetStyle_ToolButton(ui->Button_VolRange);
//    SetStyle_ToolButton(ui->Button_SelCOM);
//   SetStyle_ToolButton(ui->ToolButton_MeasureMode);

}



/**
 * @brief SetStyle_PushButton
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::SetStyle_PushButton(QPushButton *btn)
{
    btn->setStyleSheet(R"(
        QPushButton {
            /* 1. 基础外观：稍微深沉一点的工业灰 */
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #E0E0E0, stop:1 #B0B0B0);
            border: 1px solid #666666; /* 边框颜色加深，更硬朗 */
            border-radius: 6px;        /* 圆角稍微大一点点，更现代 */
            padding: 5px 10px;         /* 初始Padding */

            /* 字体 */
            font-family: "Consolas", "Courier New";
            font-size: 12pt;
            font-weight: bold;
            color: #2b2b2b;            /* 字色改为接近黑色的深灰，对比度更高 */

            min-width: 80px;
            min-height: 35px;          /* 稍微增高一点，更有点击欲望 */
            outline: none;             /* 去掉点击时的虚线框 */
        }

        /* 🖱️ 鼠标悬停 (Hover)：像金属被照亮 */
        QPushButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #F5F5F5, stop:1 #CDCDCD);
            border-color: #444444;     /* 悬停时边框变深色 */
            color: #000000;            /* 悬停时文字全黑 */
        }

        /* 👇 按下效果 (Pressed)：凹陷 + 内阴影 + 位移 */
        QPushButton:pressed {
            /* 背景反转：上深下浅，模拟物理凹陷的阴影 */
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #9E9E9E, stop:1 #C8C8C8);

            /* 内阴影边框 */
            border: 1px solid #555555;
            border-top: 2px solid #444444;   /* 顶部阴影更重 */
            border-left: 2px solid #444444;

            /* 🌟 物理位移模拟 (Padding Trick) 🌟 */
            /* 基础Padding是 5px 10px */
            /* 上和左增加，下和右减少，把文字仅仅是"挤"到了右下方 */
            padding-top: 7px;   /* +2px */
            padding-left: 12px; /* +2px */
            padding-right: 8px; /* -2px */
            padding-bottom: 3px;/* -2px */

            color: #1a1a1a;
        }

        /* 🚫 禁用状态 */
        QPushButton:disabled {
            background-color: #E6E6E6;
            color: #999999;
            border: 1px solid #CCCCCC;
        }
    )");
}


/**
 * @brief SetStyle_ToolButton
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::SetStyle_ToolButton(QToolButton *btn)
{
    btn->setStyleSheet(R"(
        QToolButton {
            /* 保持与 PushButton 一致的深色调 */
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #E0E0E0, stop:1 #B0B0B0);
            border: 1px solid #666666;
            border-radius: 6px;
            /* ToolButton 通常右边有箭头，所以右边距给大一点 */
            padding: 5px 25px 5px 10px;

            font-family: "Consolas", "Courier New";
            font-size: 12pt;
            font-weight: bold;
            color: #2b2b2b;

            min-width: 80px;
            min-height: 35px;
        }

        /* 🖱️ 悬停 */
        QToolButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #F5F5F5, stop:1 #CDCDCD);
            border-color: #444444;
        }

        /* 👇 按下 */
        QToolButton:pressed {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #9E9E9E, stop:1 #C8C8C8);
            border: 1px solid #555555;
            border-top: 2px solid #444444;
            border-left: 2px solid #444444;

            /* 位移模拟：注意右边距还得保留给箭头 */
            padding-top: 7px;
            padding-left: 12px;
            padding-right: 23px; /* 25-2 */
            padding-bottom: 3px;
        }

        /* 🔽 如果设置了 setPopupMode(InstantPopup)，Qt会自带一个小箭头 */
        /* 我们可以微调这个箭头的位置或颜色（可选） */
        QToolButton::menu-indicator {
            image: none; /* 如果你想去掉系统自带箭头，解开这行 */
            /* 或者你可以自定义一个更深色的箭头，如果不写这一段，就是Qt默认 */
            subcontrol-origin: padding;
            subcontrol-position: center right;
            right: 8px; /* 距离右边的距离 */
        }

        QToolButton:disabled {
            background-color: #E6E6E6;
            color: #999999;
            border: 1px solid #CCCCCC;
        }
    )");
}


