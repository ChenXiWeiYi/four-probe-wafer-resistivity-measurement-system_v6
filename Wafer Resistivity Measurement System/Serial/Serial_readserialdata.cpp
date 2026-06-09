#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QDataStream>
#include <QTextStream>

/**
 * @brief Widget::readSerialData 读取串口
 * @author 刘嘉诚
 * @date 2026.02.02
 */
void Widget::readSerialData(void)
{
    m_buffer.append(serialPort->readAll());

    while (m_buffer.size() >= 3){   // 帧头2B+数据长度1B
        if ((unsigned char)m_buffer.at(0) != 0xAA || (unsigned char)m_buffer.at(1) != 0x55){
            m_buffer.remove(0, 1);
            continue;
        }
        unsigned char bodyLen = (unsigned char)m_buffer.at(2);  // 第三个字节存数据+CRC长度,不包括自己和帧头

        if(bodyLen > 60){
            m_buffer.remove(0, 1);
            continue;
        }

        int totalLen = 2 + 1 + static_cast<int>(bodyLen);   // 把帧头和数据长度那个自己加进去

        if (m_buffer.size() < totalLen){ // 缓冲区没接收全
            return;
        }

        QByteArray packet = m_buffer.left(totalLen);

        // 计算 CRC
        // 校验范围：从头开始，一直算到 CRC 前一位
        unsigned short calcCRC = Calculate_CRC16(packet.left(totalLen - 2));

        // 提取收到的 CRC
        unsigned char crc_l = (unsigned char)packet.at(totalLen - 2);
        unsigned char crc_h = (unsigned char)packet.at(totalLen - 1);
        unsigned short recvCRC = (crc_h << 8) | crc_l;
//        qDebug() << "原始数据:" << packet.toHex().toUpper();
//        qDebug() << "参与计算部分:" << packet.left(totalLen - 2).toHex().toUpper();
//        qDebug() << "算出的CRC:" << QString::number(calcCRC, 16);
//        qDebug() << "收到的CRC:" << QString::number(recvCRC, 16);
        if (calcCRC == recvCRC){
            // ✅ [校验成功]

            // 提取 Payload (去掉头2, Len1，去掉尾CRC2)
            // Payload 长度 = totalLen - 2 - 1 - 2
            QByteArray payload = packet.mid(3, totalLen - 5);

            // ---> 这里是你改动的地方 <---
            // 根据 Payload 的第一个字节或者长度来判断如果不只是数据帧
            // 比如你约定：如果 Payload 长度是 6，那就是传感器数据
            // 如果 Payload[0] 是 0x01，那就是指令...
            DispatchPacket(payload); // 分发处理函数

            // 移除已处理的这帧
            m_buffer.remove(0, totalLen);
        }
        else{
            qDebug() << "CRC校验错，假头！";
            m_buffer.remove(0, 1); // 滑一个字节，重找
        }
    }
}
