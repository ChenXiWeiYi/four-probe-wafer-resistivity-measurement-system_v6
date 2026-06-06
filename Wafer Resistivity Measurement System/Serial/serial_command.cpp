#include "widget.h"
#include "ui_widget.h"

namespace {
void AppendFloat(QByteArray *data, float value)
{
    data->append(reinterpret_cast<const char*>(&value), sizeof(float));
}
}

void Widget::Command_SwitchCurrPos(void)
{
    QByteArray data;
    int mcuCurrPos = CurrentMcuCurrPos();
    data.append(static_cast<char>(0x20 + mcuCurrPos));

    int idx = CurrentPidParamIndex();
    if(idx >= 0){
        float spCurrent = static_cast<float>(Map_CurrValue.value(static_cast<CurrPos_TypeDef>(mcuCurrPos)));
        float kp = static_cast<float>(Param_used.PID_Kp[idx]);
        float ki = 0.0f;
        float kd = static_cast<float>(Param_used.PID_Kp[idx] * Param_used.PID_Td[idx]);

        if(qAbs(Param_used.PID_Ti[idx]) > 0.000001){
            ki = static_cast<float>(Param_used.PID_Kp[idx] / Param_used.PID_Ti[idx]);
        }

        data.append(static_cast<char>(mcuCurrPos));
        data.append(static_cast<char>(Param_used.PIDControlEnabled ? 1 : 0));
        AppendFloat(&data, spCurrent);
        AppendFloat(&data, kp);
        AppendFloat(&data, ki);
        AppendFloat(&data, kd);
    }

    Protocol_SendPacket(data);
}

void Widget::Command_SwitchVolRange(void)
{
    Send_ControlByte(0x60 + static_cast<int>(Param_used.VolRange));
}

void Widget::Command_StartMeasurement(void)
{
    QByteArray data;
    data.append(static_cast<char>(static_cast<unsigned char>(0xB0)));
    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        data.append(static_cast<char>(static_cast<unsigned char>(0x00)));
    }else{
        data.append(static_cast<char>(static_cast<unsigned char>(0xFF)));
    }
    Protocol_SendPacket(data);
    ui->Label_MeasureProgress->setText(QString("第%1组测量开始").arg(QString::number(MeasureState_used.cnt_MeasureGroup + 1)));
}

void Widget::Command_ModifyControlVoltage(void)
{
    float ControlVoltage = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    QByteArray data;
    data.append(static_cast<char>(0xA0));
    AppendFloat(&data, ControlVoltage);
    Protocol_SendPacket(data);
}

void Widget::Command_ReadCurrentOnly(void)
{
    Send_ControlByte((char)0x40);
}

void Widget::Command_SendPIDControlConfig(void)
{
    if(!serialPort->isOpen()){
        return;
    }

    QByteArray data;
    data.append(static_cast<char>(0xC0));
    data.append(static_cast<char>(Param_used.PIDControlEnabled ? 1 : 0));
    AppendFloat(&data, static_cast<float>(Param_used.CurrErrorBound));
    Protocol_SendPacket(data);
}

void Widget::Command_SendCustomControlVoltage(float voltage)
{
    if (voltage > 3.0f) voltage = 3.0f;
    if (voltage < 0.0f) voltage = 0.0f;

    QByteArray data;
    data.append(static_cast<char>(0xA0));
    AppendFloat(&data, voltage);
    Protocol_SendPacket(data);
}
