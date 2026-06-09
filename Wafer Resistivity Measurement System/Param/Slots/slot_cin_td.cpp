#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

/**
 * @brief Slot_cin_Td
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Slot_cin_Td(void)
{
    bool ok;
    double val = ui->cin_Td->text().toDouble(&ok);
    int idx = CurrentPidParamIndex();

    if(idx < 0){
        Popup_Window("错误", "自动档没有独立PID参数!");
        Load_PIDParamsForCurrentPosition();
        return;
    }

    if(!ok){
        Popup_Window("错误", "微分时间Td格式错误!");
        ui->cin_Td->setText(QString::number(Controller_used.Td));
        return;
    }

    if(qAbs(val - Controller_used.Td) < 0.000001) return;

    if((MeasureState_used.MeasureStage != STAGE_IDLE) || (MeasureState_used.Flag_TestCurrent == true)){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Td->setText(QString::number(Controller_used.Td));
        return;
    }

    Controller_used.Td = val;
    Param_used.PID_Td[idx] = val;
    Param_Setting_Write(NAME_PID_Td, VectorToString(Param_used.PID_Td));

    ui->cin_Td->setText(QString::number(Controller_used.Td));
}
