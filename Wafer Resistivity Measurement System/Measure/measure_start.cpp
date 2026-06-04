#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Widget::Measure_Start 测量开始
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Measure_Start(void)
{
    MeasureState_used.Time_MeasurementStart = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    MeasureState_used.cnt_MeasureGroup = 0;
    ui->ProgressBar_MeasureProgress->setValue(0);
    if(Param_used.MeasureMode == MODE_10TIMES_MULTIPOINT_MAN || Param_used.MeasureMode == MODE_10TIMES_SINGLEPOINT_MAN){
        ui->Label_MeasureProgress->setText("等待探针接触");
        MeasureState_used.MeasureStage = STAGE_MONITOR_CONTACT;
        Timer_ContactMonitor->start(200);   // 200ms轮询
    }else{
        MeasureState_used.MeasureStage = STAGE_MEASURING;
        Command_StartMeasurement();
    }
}
