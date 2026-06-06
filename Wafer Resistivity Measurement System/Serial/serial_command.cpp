#include "widget.h"
#include "ui_widget.h"

namespace {
void AppendFloat(QByteArray *data, float value)
{
    data->append(reinterpret_cast<const char*>(&value), sizeof(float));
}
}

unsigned char Widget::NextCommandSeq(void)
{
    unsigned char seq = CommStruct_used.Seq_Next;

    CommStruct_used.Seq_Next++;
    if(CommStruct_used.Seq_Next == 0){
        CommStruct_used.Seq_Next = 1;
    }

    return seq;
}

void Widget::Command_SwitchCurrPos(void)
{
    QByteArray data;
    int mcuCurrPos = CurrentMcuCurrPos();
    int idx = CurrentPidParamIndex();
    float spCurrent = 0.0f;
    float kp = 0.0f;
    float ki = 0.0f;
    float kd = 0.0f;
    float initialUk = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    bool pidEnabled = Param_used.PIDControlEnabled && (idx >= 0);

    if(idx >= 0){
        spCurrent = static_cast<float>(Map_CurrValue.value(static_cast<CurrPos_TypeDef>(mcuCurrPos)));
        kp = static_cast<float>(Param_used.PID_Kp[idx]);
        kd = static_cast<float>(Param_used.PID_Kp[idx] * Param_used.PID_Td[idx]);

        if(qAbs(Param_used.PID_Ti[idx]) > 0.000001){
            ki = static_cast<float>(Param_used.PID_Kp[idx] / Param_used.PID_Ti[idx]);
        }
    }

    data.append(static_cast<char>(0x20));
    data.append(static_cast<char>(NextCommandSeq()));
    data.append(static_cast<char>(mcuCurrPos));
    data.append(static_cast<char>(pidEnabled ? 1 : 0));
    AppendFloat(&data, spCurrent);
    AppendFloat(&data, kp);
    AppendFloat(&data, ki);
    AppendFloat(&data, kd);
    AppendFloat(&data, initialUk);

    if(!Serial_SendFrame(data)){
        return;
    }
}

void Widget::Command_SwitchVolRange(void)
{
    QByteArray data;
    data.append(static_cast<char>(0x60));
    data.append(static_cast<char>(NextCommandSeq()));
    data.append(static_cast<char>(Param_used.VolRange));
    Serial_SendFrame(data);
}

void Widget::Command_StartMeasurement(void)
{
    QByteArray data;
    data.append(static_cast<char>(static_cast<unsigned char>(0xB0)));
    data.append(static_cast<char>(NextCommandSeq()));
    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        data.append(static_cast<char>(static_cast<unsigned char>(0x00)));
    }else{
        data.append(static_cast<char>(static_cast<unsigned char>(0xFF)));
    }
    if(!Serial_SendFrame(data)){
        return;
    }
    ui->Label_MeasureProgress->setText(QString("第%1组测量开始").arg(QString::number(MeasureState_used.cnt_MeasureGroup + 1)));
}

void Widget::Command_ModifyControlVoltage(void)
{
    float ControlVoltage = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    QByteArray data;
    data.append(static_cast<char>(0xA0));
    data.append(static_cast<char>(NextCommandSeq()));
    AppendFloat(&data, ControlVoltage);
    Serial_SendFrame(data);
}

void Widget::Command_ReadCurrentOnly(void)
{
    QByteArray data;
    data.append(static_cast<char>(0x40));
    data.append(static_cast<char>(NextCommandSeq()));
    Serial_SendFrame(data);
}

void Widget::Command_Heartbeat(void)
{
    QByteArray data;
    data.append(static_cast<char>(0x70));
    data.append(static_cast<char>(NextCommandSeq()));
    Serial_SendFrame(data);
}

void Widget::Command_SendPIDControlConfig(void)
{
    if(!serialPort->isOpen()){
        return;
    }

    QByteArray data;
    data.append(static_cast<char>(0xC0));
    data.append(static_cast<char>(NextCommandSeq()));
    data.append(static_cast<char>(Param_used.PIDControlEnabled ? 1 : 0));
    AppendFloat(&data, static_cast<float>(Param_used.CurrErrorBound));
    Serial_SendFrame(data);
}

void Widget::Command_SendCustomControlVoltage(float voltage)
{
    if (voltage > 3.0f) voltage = 3.0f;
    if (voltage < 0.0f) voltage = 0.0f;

    QByteArray data;
    data.append(static_cast<char>(0xA0));
    data.append(static_cast<char>(NextCommandSeq()));
    AppendFloat(&data, voltage);
    Serial_SendFrame(data);
}
