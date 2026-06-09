#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

static QString ErrorNumberToString(unsigned char errorNumber);



/**
 * @brief Widget::Handle_ControlByte 控制字解析
 * @param 载荷
 * @author 刘嘉诚
 * @date  2026.06.06
 */
void Widget::DispatchPacket(const QByteArray &payload)
{
    if(payload.isEmpty()){
        ui->logText_1->append("上位机错误：收到空Payload");
        return;
    }

    unsigned char CtrlByte = (unsigned char)payload.at(0);


    switch(CtrlByte & 0xF0){
		case(0x10):
			Answer_AckNack(payload);
			break;
        case(0x20):
            ui->logText_1->append("上位机提示：收到旧版电流档位回显，已忽略");
            break;
		case(0x30):
			Answer_OperationDone(payload);
			break;
        case(0x40):
            Answer_ReadCurrentOnly(payload);
            break;
        case(0x50):
            Answer_VoltageCurrentRecieve(payload);
//            qDebug() << "接收到电压电流值答复";
            break;
        case(0x60): // 电压档位切换答复
            ui->logText_1->append("上位机提示：收到旧版电压档位回显，已忽略");
            break;
        case(0xA0):
            ui->logText_1->append("上位机提示：收到旧版压控修改回显，已忽略");
            break;
        case(0xB0):
            Answer_MeasureState(payload);
            qDebug() << "接收到测量状态答复";
            break;
        case(0xC0):
            ui->logText_1->append("上位机提示：收到旧版PID配置回显，已忽略");
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
 * @brief Answer_AckNack
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Answer_AckNack(const QByteArray &payload)
{
    if(payload.size() < 5){
        ui->logText_1->append("上位机错误：ACK/NACK数据包长度不足");
        return;
    }

    unsigned char seq = static_cast<unsigned char>(payload.at(1));
    unsigned char originCtrlByte = static_cast<unsigned char>(payload.at(2));
    unsigned char status = static_cast<unsigned char>(payload.at(3));
    unsigned char errorNumber = static_cast<unsigned char>(payload.at(4));

    if(!CommStruct_used.Flag_isWaitingEcho){
        ui->logText_1->append(QString("收到无等待命令的ACK/NACK: seq=%1 cmd=0x%2")
                              .arg(seq)
                              .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper());
        return;
    }

    if(seq != CommStruct_used.Seq_Waiting || originCtrlByte != CommStruct_used.CtrlByte_Waiting){
        ui->logText_1->append(QString("ACK/NACK不匹配: 等待seq=%1 cmd=0x%2, 收到seq=%3 cmd=0x%4")
                              .arg(CommStruct_used.Seq_Waiting)
                              .arg(CommStruct_used.CtrlByte_Waiting, 2, 16, QLatin1Char('0'))
                              .arg(seq)
                              .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper());
        return;
    }

    Timer_EchoMonitor->stop();
    CommStruct_used.Flag_isWaitingEcho = false;
    CommStruct_used.Error_LastAck = errorNumber;

    if(status == 0x00){
        CommStruct_used.Flag_isEchoVerified = true;
        switch(originCtrlByte){
        case 0x20:
            CommStruct_used.Flag_isWaitingDone = true;
            CommStruct_used.Seq_WaitingDone = seq;
            CommStruct_used.CtrlByte_WaitingDone = originCtrlByte;
            CommStruct_used.Error_LastDone = 0;
            Timer_EchoMonitor->start(3000);
            ui->logText_1->append("Current position command accepted, waiting operation done");
            break;
        case 0x60:
            Answer_VoltageRange();
            break;
        case 0x70:
            CommStruct_used.Cnt_HeartbeatLost = 0;
            if(CommStruct_used.Flag_isSerialProbing){
                Handle_SerialConnected(serialPort->portName(), true);
                Command_SendPIDControlConfig();
            }
            break;
        case 0xA0:
            Answer_ModifyControlVoltage();
            break;
        case 0xB0:
            ui->logText_1->append("测量命令已被单片机接受");
            break;
        case 0xC0:
            ui->logText_1->append("PID控制配置已发送");
            break;
        default:
            break;
        }
        return;
    }

    CommStruct_used.Flag_isEchoVerified = false;
    CommStruct_used.Flag_isWaitingDone = false;
    ui->logText_1->append(QString("单片机NACK: cmd=0x%1, err=%2(%3)")
                          .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper()
                          .arg(errorNumber)
                          .arg(ErrorNumberToString(errorNumber)));

    switch(originCtrlByte){
    case 0x20:
        Answer_CurrentPosition();
        break;
    case 0x60:
        Answer_VoltageRange();
        break;
    case 0x70:
        if(CommStruct_used.Flag_isSerialProbing){
            Handle_SerialDisconnected("设备识别失败", false);
        }
        break;
    case 0xA0:
        Answer_ModifyControlVoltage();
        break;
    case 0xB0:
        MeasureState_used.MeasureStage = STAGE_IDLE;
        Popup_Window("错误", "测量命令发送失败: " + ErrorNumberToString(errorNumber));
        break;
    case 0xC0:
        Popup_Window("错误", "PID配置发送失败: " + ErrorNumberToString(errorNumber));
        break;
    default:
        break;
    }
}


/**
 * @brief Handle operation completion frame 0x30.
 * @param payload Payload in format: 0x30, seq, original command, status, error.
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Answer_OperationDone(const QByteArray &payload)
{
    if(payload.size() < 5){
        ui->logText_1->append("Operation done packet length error");
        return;
    }

    unsigned char seq = static_cast<unsigned char>(payload.at(1));
    unsigned char originCtrlByte = static_cast<unsigned char>(payload.at(2));
    unsigned char status = static_cast<unsigned char>(payload.at(3));
    unsigned char errorNumber = static_cast<unsigned char>(payload.at(4));

    if(!CommStruct_used.Flag_isWaitingDone){
        ui->logText_1->append(QString("Received operation done without waiting command: seq=%1 cmd=0x%2")
                              .arg(seq)
                              .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper());
        return;
    }

    if(seq != CommStruct_used.Seq_WaitingDone || originCtrlByte != CommStruct_used.CtrlByte_WaitingDone){
        ui->logText_1->append(QString("Operation done mismatch: waiting seq=%1 cmd=0x%2, received seq=%3 cmd=0x%4")
                              .arg(CommStruct_used.Seq_WaitingDone)
                              .arg(CommStruct_used.CtrlByte_WaitingDone, 2, 16, QLatin1Char('0'))
                              .arg(seq)
                              .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper());
        return;
    }

    Timer_EchoMonitor->stop();
    CommStruct_used.Flag_isWaitingDone = false;
    CommStruct_used.Error_LastDone = errorNumber;

    if(status == 0x00){
        CommStruct_used.Flag_isEchoVerified = true;
        if(originCtrlByte == 0x20){
            Answer_CurrentPosition();
        }
        return;
    }

    CommStruct_used.Flag_isEchoVerified = false;
    ui->logText_1->append(QString("Operation failed: cmd=0x%1, err=%2(%3)")
                          .arg(originCtrlByte, 2, 16, QLatin1Char('0')).toUpper()
                          .arg(errorNumber)
                          .arg(ErrorNumberToString(errorNumber)));

    if(originCtrlByte == 0x20){
        Answer_CurrentPosition();
    }
}

/**
 * @brief Answer current position switch result.
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Answer_CurrentPosition(void)
{
    if(CommStruct_used.Flag_isEchoVerified){
        Popup_Window("提示","电流档位切换成功");
        ui->Button_CurrPos->setText(Map_CurrPos.value(static_cast<CurrPos_TypeDef>(Param_used.CurrPos)));
        Param_Setting_Write(NAME_CurrPos, Param_used.CurrPos);   // 存入文件
        ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
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
    if(payload.size() < 2){
        ui->logText_1->append("上位机错误：测量状态数据包长度不足");
        return;
    }

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
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Answer_ErrorRecieve(const QByteArray &payload)
{
    if(payload.size() < 2){
        ui->logText_1->append("上位机错误：错误数据包长度不足");
        return;
    }

    unsigned char ErrorNumber = (unsigned char)payload.at(1);
    ui->logText_1->append("单片机主动错误: " + ErrorNumberToString(ErrorNumber));
}


/**
 * @brief Answer_CurrentForControl
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Answer_CurrentForControl(const QByteArray &payload)
{
    if(payload.size() < 4){
        return;
    }
    QByteArray CurrentRaw = payload.mid(1, 3);
    double Current = DataProcess_ADC2_Current(CurrentRaw);
    AppendValueToFile(Current, VALUE_CURRENT);
}

/**
 * @brief ErrorNumberToString
 * @author 刘嘉诚
 * @date 2026.06.08
 */
static QString ErrorNumberToString(unsigned char errorNumber)
{
    switch(errorNumber){
    case 0x00:
        return "无错误";
    case 0x01:
        return "未知控制字";
    case 0x02:
        return "未知测量方向";
    case 0x03:
        return "电压档位错误";
    case 0x04:
        return "CRC校验错误";
    case 0x05:
        return "未知电流档位";
    case 0x06:
        return "没有合适测量档位";
    case 0x07:
        return "欠量程";
    case 0x08:
        return "过量程";
    case 0x09:
        return "电流误差超限";
    case 0x0A:
        return "PID配置数据长度错误";
    case 0x0B:
        return "数据包长度错误";
    case 0x0C:
        return "参数值错误";
    case 0x0D:
        return "Device busy";
    default:
        return QString("未知错误类型(%1)").arg(errorNumber);
    }
}
