#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

/**
 * @brief Widget::Handle_ControlByte 控制字解析
 * @param 载荷
 * @date  2026.01.15
 */
void Widget::DispatchPacket(const QByteArray &payload)
{
    // 判断回显是否通过
    if(CommStruct_used.Flag_isWaitingEcho){
        if(CommStruct_used.PayLoad_LastSend == payload){
            CommStruct_used.Flag_isEchoVerified = true;
            CommStruct_used.Flag_isWaitingEcho = false;
            Timer_EchoMonitor->stop();
        }else{
            CommStruct_used.Flag_isEchoVerified = false;
            ui->logText_1->append("回显内容不一致");
            qDebug()<<"回显内容不一致";
        }
    }
    unsigned char CtrlByte = (unsigned char)payload.at(0);
    switch(CtrlByte & 0xF0){
        case(0x20):
            Answer_CurrentPosition();
            qDebug() << "接收到通道切换答复";
            break;
        case(0x40):
            Answer_ReadCurrentOnly(payload);
            break;
        case(0x50):
            Answer_VoltageCurrentRecieve(payload);
//            qDebug() << "接收到电压电流值答复";
            break;
        case(0x60): // 电压档位切换答复
            Answer_VoltageRange();
            qDebug() << "接收到电压档位切换答复";
            break;
        case(0xA0):
            Answer_ModifyControlVoltage();
            qDebug() << "接收到压控修改答复";
            break;
        case(0xB0):
            Answer_MeasureState(payload);
            qDebug() << "接收到测量状态答复";
            break;
        case(0xD0):
            Answer_CurrentForControl(payload);
            break;
        case(0xE0):
            qDebug() << "接收到测试";
            ui->logText_1->append(QString("接收到测试"));
            break;
        case(0xF0):
            Answer_ErrorRecieve(payload);
            qDebug() << "接收到报错答复";
            break;
        default:
            ui->logText_1->append(QString("上位机错误：未知答复控制字"));
            break;
    }
}


/**
 * @brief 答复:电流档位切换
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Answer_CurrentPosition(void)
{
    if(CommStruct_used.Flag_isEchoVerified){
        Popup_Window("提示","电流档位切换成功");
        ui->Button_CurrPos->setText(Map_CurrPos.value(static_cast<CurrPos_TypeDef>(Param_used.CurrPos)));
        Param_Setting_Write(NAME_CurrPos, Param_used.CurrPos);   // 存入文件
        ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
        Command_ModifyControlVoltage();
    }else{
        ui->Button_CurrPos->setText("---");
        Popup_Window("错误","电流档位切换失败");
    }
}

/**
 * @brief Widget::Answer_VoltageRange 答复:电压档位切换
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Answer_VoltageRange(void)
{
    if(CommStruct_used.Flag_isEchoVerified){
        Popup_Window("提示","电压档位切换成功");
        ui->Button_VolRange->setText(Map_VolRange.value(static_cast<VolRange_TypeDef>(Param_used.VolRange)));
        Param_Setting_Write(NAME_VolRange, Param_used.VolRange);   // 存入文件
    }else{
        ui->Button_VolRange->setText("---");
        Popup_Window("错误","电压档位切换失败");
    }
}




/**
 * @brief Widget::Answer_VoltageCurrentRecieve 答复:电压电流值接收
 * @param 载荷
 * @author 刘嘉诚
 * @date 2026.02.15
 */
void Widget::Answer_VoltageCurrentRecieve(const QByteArray &payload)
{
    if(payload.size() < 7){
        Popup_Window("错误", "数据包长度不足");
        return;
    }

    // 1. 分别提取数据段
    QByteArray VoltageRaw = payload.mid(1, 3); // 第1,2,3字节
    QByteArray CurrentRaw = payload.mid(4, 3); // 第4,5,6字节

    // 2. 分别处理 ADC
    double Voltage = DataProcess_ADC1_Voltage(VoltageRaw);
    double Current = DataProcess_ADC2_Current(CurrentRaw);

    // 3. 只有在完整的测量指令下，我们才计算电阻率并保存
    Process_Resistivity(Voltage, Current);
}




/**
 * @brief Widget::Answer_MeasureState 答复:测量状态
 * @param 载荷
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Answer_MeasureState(const QByteArray &payload)
{
    unsigned char Flag = (unsigned char)payload.at(1);
    switch(Flag){
    case(0x00):
        ui->logText_1->append(QString("接收到正向测量指令"));
        break;
    case(0xFF):
        ui->logText_1->append(QString("接收到反向测量指令"));
        break;
    case(0x55):
        ui->logText_1->append(QString("正向测量完成"));
        Measure_Complete();
        break;
    case(0xAA):
        ui->logText_1->append(QString("反向测量完成"));
        Measure_Complete();
        break;
    }
}

/**
 * @brief Widget::Answer_ErrorRecieve 答复:单片机错误
 * @param 载荷
 */
void Widget::Answer_ErrorRecieve(const QByteArray &payload)
{
    unsigned char ErrorNumber = (unsigned char)payload.at(1);
    switch(ErrorNumber){
    case(0x01):
        qDebug()<<"未知方向";
        break;
    case(0x02):
        ui->logText_1->append("单片机错误: 控制字未知");
        break;
    case(0x0E):
        ui->logText_1->append("单片机错误: 未知错误");
        break;
    default:
        ui->logText_1->append(QString("单片机错误: 未知错误类型(%1)").arg(ErrorNumber));
        break;
    }
}


void Widget::Answer_CurrentForControl(const QByteArray &payload)
{
    if(payload.size() < 4){
        return;
    }
    QByteArray CurrentRaw = payload.mid(1, 3);
    double Current = DataProcess_ADC2_Current(CurrentRaw);
    AppendValueToFile(Current, VALUE_CURRENT);
}
