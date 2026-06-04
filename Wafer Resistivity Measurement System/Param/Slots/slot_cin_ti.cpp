#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

void Widget::Slot_cin_Ti(void)
{
    bool ok;
    double val = ui->cin_Ti->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "积分时间Ti格式错误!");
        ui->cin_Ti->setText(QString::number(Controller_used.Ti));
        return;
    }

    if (qAbs(val - Controller_used.Ti) < 0.000001) return;

    if((MeasureState_used.MeasureStage != STAGE_IDLE) || (MeasureState_used.Flag_TestCurrent == true)){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Ti->setText(QString::number(Controller_used.Ti));
        return;
    }

    Controller_used.Ti = val;

    ui->cin_Ti->setText(QString::number(Controller_used.Ti));
}
