#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QAction>

void Widget::onMenuCurrPosTriggered(QAction *action)
{
    int CurrPos_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        return;
    }

    Param_used.CurrPos = CurrPos_i;
    Load_PIDParamsForCurrentPosition();
    ui->Button_CurrPos->setText("正在切换");
    ui->cin_ControlVoltage->setText("正在切换电流档位");
    Controller_used.Last_uk = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    Command_SwitchCurrPos();
}

void Widget::onMenuVolRangeTriggered(QAction *action)
{
    int VolRange_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        return;
    }

    ui->Button_VolRange->setText("正在切换");
    Param_used.VolRange = VolRange_i;
    Command_SwitchVolRange();
}

void Widget::onMenuMeasureModeTriggered(QAction *action)
{
    int MeasureMode_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        return;
    }

    Param_used.MeasureMode = static_cast<MeasureMode_TypeDef>(MeasureMode_i);
    Param_Setting_Write(NAME_MeasureMode, MeasureMode_i);

    ui->ToolButton_MeasureMode->setText(action->text());
}

void Widget::onMenuCOMTriggered(QAction *action)
{
    QString comName = action->text();

    if(!Open_SerialPortByName(comName, false)){
        action->setChecked(false);
    }
}
