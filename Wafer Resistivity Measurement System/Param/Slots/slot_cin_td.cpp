#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

void Widget::Slot_cin_Td(void)
{
    bool ok;
    double val = ui->cin_Td->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "微分时间Td格式错误!");
        ui->cin_Td->setText(QString::number(Controller_used.Td));
        return;
    }

    if (qAbs(val - Controller_used.Td) < 0.000001) return;

    if((MeasureState_used.MeasureStage != STAGE_IDLE) || (MeasureState_used.Flag_TestCurrent == true)){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Td->setText(QString::number(Controller_used.Td));
        return;
    }

    Controller_used.Td = val;

    ui->cin_Td->setText(QString::number(Controller_used.Td));
}
