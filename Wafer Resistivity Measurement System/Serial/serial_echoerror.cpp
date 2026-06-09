#include "widget.h"

/**
 * @brief onTimerEchoMonitorTimeout
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::onTimerEchoMonitorTimeout(void)
{
    if(CommStruct_used.Flag_isWaitingEcho){
        unsigned char originCtrlByte = CommStruct_used.CtrlByte_Waiting;

        CommStruct_used.Flag_isWaitingEcho = false;
        CommStruct_used.Flag_isEchoVerified = false;

        if(originCtrlByte == 0x70){
            if(CommStruct_used.Flag_isSerialProbing){
                Handle_SerialDisconnected("设备识别超时", false);
                return;
            }

            CommStruct_used.Cnt_HeartbeatLost++;
            if(CommStruct_used.Cnt_HeartbeatLost >= 3){
                Handle_SerialDisconnected("通信无响应", true);
            }
            return;
        }

        Popup_Window("Error", "MCU ACK/NACK response timeout");
        return;
    }

    if(CommStruct_used.Flag_isWaitingDone){
        unsigned char originCtrlByte = CommStruct_used.CtrlByte_WaitingDone;

        CommStruct_used.Flag_isWaitingDone = false;
        CommStruct_used.Flag_isEchoVerified = false;
        Popup_Window("Error", "MCU operation done response timeout");

        if(originCtrlByte == 0x20){
            Answer_CurrentPosition();
        }
    }
}
