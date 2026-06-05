#ifndef Control_Current_Value_H
#define Control_Current_Value_H

#include "sys.h"
#include <stdbool.h>

void CurrentControl_SetConfig(bool enabled, float errorBoundPercent);
void CurrentControl_SetEnabled(bool enabled);
void CurrentControl_SetParams(uint8_t currentPos, float spCurrent, float kp, float ki, float kd);
void CurrentControl_SetOutputVoltage(float voltage);
void CurrentControl_UpdateFromADC(void);
float CurrentControl_ConvertADC2ToCurrent(void);

#endif
