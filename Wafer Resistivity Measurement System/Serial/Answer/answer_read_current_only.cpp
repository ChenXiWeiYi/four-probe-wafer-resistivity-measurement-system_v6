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
    ui->Label_Current->setText(QString::number(Current));

    if(MeasureState_used.Flag_TestCurrent){
        if(MeasureState_used.Flag_FirstReadCurrent){
            MeasureState_used.Flag_FirstReadCurrent = false;
        }
        Timer_ContactMonitor->start(10);
    }
}
