#ifndef Command_Handler_H
#define Command_Handler_H

#include <string.h>
#include <stdbool.h>
#include "sys.h"


/** Command_Handler.c **/
void Command_CurrPosSwitch(uint8_t *payload, uint8_t payload_len);
void Command_CurrentControlInputModify(uint8_t *p_SP_Current_u8);
void Command_PIDControlConfig(uint8_t *payload, uint8_t payload_len);
void Command_ReadCurrentOnly(void);
void Command_StartMeasurement(uint8_t MeasureDirection_u8);
void Command_VoltRangeSwitch(uint8_t CtrlByte);
bool Return_Direction(void);

#endif
