#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

/**
 * @brief Widget::Answer_ModifyControlVoltage 答复:恒流源压控电压修改
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Answer_ModifyControlVoltage(void)
{
    if(CommStruct_used.Flag_isEchoVerified){
        ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
        QString valStr = VectorToString(Param_used.ControlVoltages);
        Controller_used.SP_Current = Map_CurrValue.value(static_cast<CurrPos_TypeDef>(Param_used.CurrPos));
   //     Controller_used.Last_uk = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
        Param_Setting_Write(NAME_ControlVoltages, valStr);
        if(MeasureState_used.Flag_TestCurrent == false){    // 自控的时候别弹窗口
            Popup_Window("提示","恒流源压控电压修改成功");
        }else{
            Timer_ContactMonitor->start(10); // 确定压控电压改成功了再测电流
        }
    }else{
        ui->cin_ControlVoltage->clear();
        Popup_Window("错误","恒流源压控电压修改失败");
    }
}
