#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

void Widget::Answer_ReadCurrentOnly(const QByteArray &payload)
{

    if(payload.size() < 4){
        return;
    }
    QByteArray CurrentRaw = payload.mid(1, 3);
    double Current = DataProcess_ADC2_Current(CurrentRaw);

    AppendValueToFile(Current, VALUE_CURRENT);
  //   Timer_ContactMonitor->start(10);
    ui->Label_Current->setText(QString::number(Current));
    if(MeasureState_used.Flag_TestCurrent){
        if(MeasureState_used.Flag_FirstReadCurrent){
            MeasureState_used.Flag_FirstReadCurrent = false;
            Timer_ContactMonitor->start(10); // 重新开始轮询
            return;
        }

        if(!Param_used.PIDControlEnabled){
            Timer_ContactMonitor->start(10);
            return;
        }

        Controller_used.PV_Current += Current;
        if(MeasureState_used.cnt_Curr == 9){
            double PV = Controller_used.PV_Current;
            PV = PV / 10;
            ui->Label_Current->setText(QString::number(PV));
            ControlLoop_Update(PV);
            MeasureState_used.cnt_Curr = 0;
            Controller_used.PV_Current = 0;
        }else{
            Timer_ContactMonitor->start(10); // 重新开始轮询
            MeasureState_used.cnt_Curr ++;
        }
    }

#if 0
    const double Threshold = 1e-8; // 阈值
    if(MeasureState_used.MeasureStage == STAGE_MONITOR_CONTACT){
        // 如果在等待接触，且电流 > 阈值
        if (std::abs(Current) > Threshold) {
             ui->logText_1->append("探针已接触，触发测量...");
             MeasureState_used.MeasureStage = STAGE_MEASURING;
             Command_StartMeasurement();   // 发送完整测量指令(0xB0)
        }
    }else if (MeasureState_used.MeasureStage == STAGE_MONITOR_RELEASE) {
        // 如果在等待释放，且电流 < 阈值
        if (std::abs(Current) < Threshold) {
             ui->logText_1->append("探针已释放，等待下次...");
             MeasureState_used.MeasureStage = STAGE_MONITOR_CONTACT;
             Timer_ContactMonitor->start(200); // 重新开始轮询
        }
    }
#endif
}
