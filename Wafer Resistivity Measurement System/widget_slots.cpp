#include "widget.h"
#include "ui_widget.h"


/** 恒流源控制电压发送 **/
void Widget::onButtonSendControlVoltageClicked() { Command_ModifyControlVoltage(); }

/** 电流档位发送 **/
void Widget::onButtonSendCurrentPositionClicked() { Command_SwitchCurrPos(); }

/** 电压档位发送 **/
void Widget::onButtonSendVoltageRangeClicked() { Command_SwitchVolRange(); }

/** 测量开始 **/
void Widget::onButtonMeasStartClicked(){
    if(MeasureState_used.MeasureStage != STAGE_IDLE){   // 判断是不是没测完
        Popup_Window("错误","正在测量,请勿重复点击!");
    }else if(Measure_CheckParam()){ // 检查参数合不合理
        Update_GeometryCorrectionFactor();  // 更新几何参数,完整的测量就更这一回
        ui->TableWidget_f->clear();
        ui->TableWidget_r->clear();
        Measure_Start();
    }
}



