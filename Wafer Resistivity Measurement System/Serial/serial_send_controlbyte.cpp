#include "widget.h"
#include "ui_widget.h"

/**
 * @brief Widget::Send_ControlByte 发送控制字至单片机
 * @param CtrlByte 待发送的控制字
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Send_ControlByte(char CtrlByte)
{
    QByteArray data;
    data.append(CtrlByte); // 只有一个字节的命令
    Protocol_SendPacket(data);
}
