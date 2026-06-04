#include "widget.h"
#include "ui_widget.h"

void Widget::Measure_Complete(void)
{
    MeasureState_used.cnt_MeasureTimes = 0;
    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        ui->logText_1->append(QString("正向数据保存完成"));
        MeasureState_used.MeasureDirection = MEASUREDIRECTION_REVERSE;
        Command_StartMeasurement();
    }else{
        ui->logText_1->append(QString("反向数据保存完成"));
        MeasureState_used.MeasureDirection = MEASUREDIRECTION_FORWARD;
        MeasureState_used.cnt_MeasureGroup ++;
        switch(Param_used.MeasureMode){
        case(MODE_SINGLE):
            Measure_Complete_MODE_SINGLE();
            break;
        case(MODE_10TIMES_SINGLEPOINT_AUTO):
            Measure_Complete_MODE_10TIMES_SINGLEPOINT_AUTO();
            break;
        case(MODE_10TIMES_SINGLEPOINT_MAN):
            Measure_Complete_MODE_10TIMES_SINGLEPOINT_MAN();
            break;
        default:
            Popup_Window("不好意思","该测量模式还没做,当单次测量用.\n测量完成");
            ui->ProgressBar_MeasureProgress->setValue(100);
            ui->Label_MeasureProgress->setText("测量完成");
            break;
        }
    }
}


void Widget::Measure_Complete_MODE_SINGLE(void){
    ui->ProgressBar_MeasureProgress->setValue(100);
    MeasureState_used.MeasureStage = STAGE_IDLE;
    ui->Label_MeasureProgress->setText("测量完成");
    Popup_Window("提示","测量完成");
}

void Widget::Measure_Complete_MODE_10TIMES_SINGLEPOINT_AUTO(void){
    if(MeasureState_used.cnt_MeasureGroup >= 10){
        MeasureState_used.cnt_MeasureGroup = 0;
        MeasureState_used.MeasureStage = STAGE_IDLE;
        ui->Label_MeasureProgress->setText("测量完成");
        Popup_Window("提示","测量完成");
    }else{
        ui->ProgressBar_MeasureProgress->setValue(10 * MeasureState_used.cnt_MeasureGroup);
        ui->Label_MeasureProgress->setText(QString("等待第%1次测量").arg(QString::number(MeasureState_used.cnt_MeasureGroup + 1)));
        Timer_MeasureInterval->start(2000);
    }
    ui->ProgressBar_MeasureProgress->setValue(10 * MeasureState_used.cnt_MeasureGroup);
}


void Widget::Measure_Complete_MODE_10TIMES_SINGLEPOINT_MAN(void)
{
    if(MeasureState_used.cnt_MeasureGroup >= 10){
        MeasureState_used.MeasureStage = STAGE_IDLE;
        ui->Label_MeasureProgress->setText("测量完成");
        Popup_Window("提示","测量完成");
    }else{
        ui->Label_MeasureProgress->setText("等待探针抬起");
        MeasureState_used.MeasureStage = STAGE_MONITOR_RELEASE;
        Timer_ContactMonitor->start(200);
    }
    ui->ProgressBar_MeasureProgress->setValue(10 * MeasureState_used.cnt_MeasureGroup);
}
