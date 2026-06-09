#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QByteArray>
#include <QString>
/**
 * @brief Widget::Calculate_CRC16 CRC校验
 * @param data
 * @return
 * @author 刘嘉诚
 * @date 2026.06.08
 */
unsigned short Widget::Calculate_CRC16(const QByteArray &data)
{
    // 强制使用 32 位变量来运算，避免溢出干扰
    unsigned int crc = 0xFFFF;
    unsigned int poly = 0xA001;

    for (int i = 0; i < data.size(); ++i) {
        unsigned char byte = static_cast<unsigned char>(data.at(i));

        crc ^= byte; // 异或数据

        for (int j = 0; j < 8; ++j) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= poly;
            } else {
                crc >>= 1;
            }
        }
        // 【关键防御】每次运算完，强制砍掉高位，只留16位
        crc &= 0xFFFF;

        // 打印第一轮的中间结果
        if (i == 0) {
//           qDebug() << "Byte 0 (AA) Result:" << QString::number(crc, 16);
        }
    }

    return (unsigned short)crc;
}


