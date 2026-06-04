#include "widget.h"
#include "ui_widget.h"


/**
 * @brief Widget::Command_SwitchCurrPos 指令:切换电流档位
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Command_SwitchCurrPos(void)
{
    Send_ControlByte(0x20 + ( 7 - static_cast<int>(Param_used.CurrPos)));  // 0x20是电流档位切换的控制位
}

/**
 * @brief Widget::Command_SwitchVolRange 指令:切换电压档位
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Command_SwitchVolRange(void)
{
    Send_ControlByte(0x60 + static_cast<int>(Param_used.VolRange));  // 0x60是电压档位切换的控制位
}

/**
 * @brief Widget::Command_StartMeasurement 指令:开始测量
 * @author 刘嘉诚
 * @date 2026.02.17
 */
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

/**
 * @brief Widget::Command_ModifyControlVoltage 指令:设置恒流源控制电压
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Command_ModifyControlVoltage(void)
{
    float ControlVoltage = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    QByteArray data;
    data.append(static_cast<char>(0xA0));
    data.append(reinterpret_cast<const char*>(&ControlVoltage), sizeof(float));
    Protocol_SendPacket(data);
}

/**
 * @brief Widget::Command_ReadCurrentOnly 指令:读电流
 * @author 刘嘉诚
 * @date 2026.02.19
 */
void Widget::Command_ReadCurrentOnly(void)
{
    Send_ControlByte((char)0x40);
}

/**
 * @brief Widget::Command_SendCustomControlVoltage 闭环控制专用：直发DAC电压
 * @param voltage 算出来的控制电压 (0~3V)
 */
void Widget::Command_SendCustomControlVoltage(float voltage)
{
    // 单片机DAC极限是3V，保护一下
    if (voltage > 3.0f) voltage = 3.0f;
    if (voltage < 0.0f) voltage = 0.0f;

    QByteArray data;
    data.append(static_cast<char>(0xA0)); // 压控指令字
    data.append(reinterpret_cast<const char*>(&voltage), sizeof(float));
    Protocol_SendPacket(data);
}
