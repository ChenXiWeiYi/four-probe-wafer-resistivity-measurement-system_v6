#include "widget.h"

void Widget::onTimerEchoMonitorTimeout(void)
{
    if(CommStruct_used.Flag_isWaitingEcho){
        CommStruct_used.Flag_isWaitingEcho = false;
        CommStruct_used.Flag_isEchoVerified = false;
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
