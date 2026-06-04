#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QDataStream>
#include <QTextStream>

/**
 * @brief Widget::Protocol_SendPacket Qt版的协议打包发送函数
 * @param payload 要发送的纯数据 (包含命令字)
 * 格式: AA 55 [Len] [Payload...] [CRC_L] [CRC_H]
 */
void Widget::Protocol_SendPacket(const QByteArray &payload)
{
    QByteArray sendBuffer;

    // 1. 帧头
    sendBuffer.append((char)0xAA);
    sendBuffer.append((char)0x55);

    // 2. 长度 (Payload长度 + CRC长度2)
    unsigned char len = (unsigned char)(payload.size() + 2);
    sendBuffer.append((char)len);

    // 3. 载荷
    sendBuffer.append(payload);

    // 4. 计算 CRC (范围: 头(2) + Len(1) + Payload)
    // 注意：Calculate_CRC16 计算的是整个前面的部分
    unsigned short crc = Calculate_CRC16(sendBuffer);

    // 5. 追加 CRC (低位在前)
    sendBuffer.append((char)(crc & 0xFF));
    sendBuffer.append((char)((crc >> 8) & 0xFF));


    CommStruct_used.PayLoad_LastSend = payload;
    CommStruct_used.Flag_isWaitingEcho = true;
    Timer_EchoMonitor->start(1000);

    // 6. 发送
    serialPort->write(sendBuffer);


    // 调试打印
    // qDebug() << "Qt发送:" << sendBuffer.toHex().toUpper();
}
