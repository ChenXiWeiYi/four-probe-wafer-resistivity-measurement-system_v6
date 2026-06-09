#include "widget.h"

/**
 * @brief onTimerMeasureIntervalTimeout
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::onTimerMeasureIntervalTimeout(void)
{
    Command_StartMeasurement();
}

/**
 * @brief onTimerContactMonitorTimeout
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::onTimerContactMonitorTimeout()
{
    Command_ReadCurrentOnly();
}

