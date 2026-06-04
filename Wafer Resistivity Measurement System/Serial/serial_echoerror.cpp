#include "widget.h"

void Widget::onTimerEchoMonitorTimeout(void)
{
    CommStruct_used.Flag_isWaitingEcho = false;
    Popup_Window("错误","单片机回显校验1s失败");
}

