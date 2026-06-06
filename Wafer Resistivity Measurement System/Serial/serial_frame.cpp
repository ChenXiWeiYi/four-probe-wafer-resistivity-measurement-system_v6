#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QDataStream>
#include <QTextStream>

/**
 * @brief Widget::Serial_SendFrame 串口协议帧打包发送函数
 * @param payload 待发送的Payload数据，包含控制字和seq
 *
 * 帧格式: AA 55 [Len] [Payload...] [CRC_L] [CRC_H]
 * @author 刘嘉诚
 * @date 2026.06.04
 */
bool Widget::Serial_SendFrame(const QByteArray &payload)
{
    QByteArray sendBuffer;
    bool commandNeedsAck = false;

    sendBuffer.append((char)0xAA);
    sendBuffer.append((char)0x55);

    unsigned char len = (unsigned char)(payload.size() + 2);
    sendBuffer.append((char)len);
    sendBuffer.append(payload);

    unsigned short crc = Calculate_CRC16(sendBuffer);
    sendBuffer.append((char)(crc & 0xFF));
    sendBuffer.append((char)((crc >> 8) & 0xFF));

    if(payload.size() >= 2){
        unsigned char ctrlByte = static_cast<unsigned char>(payload.at(0));
        if(ctrlByte == 0x20 || ctrlByte == 0x40 || ctrlByte == 0x60 ||
           ctrlByte == 0xA0 || ctrlByte == 0xB0 || ctrlByte == 0xC0){
            commandNeedsAck = true;
        }
    }

    if(commandNeedsAck && (CommStruct_used.Flag_isWaitingEcho || CommStruct_used.Flag_isWaitingDone)){
        ui->logText_1->append(QString("上一条指令未完成，本次指令未发送: cmd=0x%1")
                              .arg(static_cast<unsigned char>(payload.at(0)), 2, 16, QLatin1Char('0')).toUpper());
        return false;
    }

    if(commandNeedsAck){
        CommStruct_used.PayLoad_LastSend = payload;
        CommStruct_used.Seq_Waiting = static_cast<unsigned char>(payload.at(1));
        CommStruct_used.CtrlByte_Waiting = static_cast<unsigned char>(payload.at(0));
        CommStruct_used.Flag_isWaitingEcho = true;
        CommStruct_used.Flag_isEchoVerified = false;
        Timer_EchoMonitor->start(1000);
    }

    if(serialPort->write(sendBuffer) < 0){
        if(commandNeedsAck){
            CommStruct_used.Flag_isWaitingEcho = false;
            CommStruct_used.Flag_isEchoVerified = false;
            Timer_EchoMonitor->stop();
        }
        return false;
    }

    return true;
}
