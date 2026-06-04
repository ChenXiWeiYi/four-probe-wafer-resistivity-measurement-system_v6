#include "widget.h"

void Widget::onTimerMeasureIntervalTimeout(void)
{
    Command_StartMeasurement();
}

void Widget::onTimerContactMonitorTimeout()
{
    Command_ReadCurrentOnly();
}

