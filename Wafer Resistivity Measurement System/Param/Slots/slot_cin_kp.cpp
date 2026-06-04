#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

void Widget::Slot_cin_Kp(void)
{
    bool ok;
    double val = ui->cin_Kp->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "比例系数Kp格式错误!");
        ui->cin_Kp->setText(QString::number(Controller_used.Kp));
        return;
    }

    if (qAbs(val - Controller_used.Kp) < 0.000001) return;

    if((MeasureState_used.MeasureStage != STAGE_IDLE) || (MeasureState_used.Flag_TestCurrent == true)){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Kp->setText(QString::number(Controller_used.Kp));
        return;
    }

    Controller_used.Kp = val;

    ui->cin_Kp->setText(QString::number(Controller_used.Kp));
}
