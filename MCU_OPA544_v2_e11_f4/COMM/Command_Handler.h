#ifndef Command_Handler_H
#define Command_Handler_H

#include <string.h>
#include <stdbool.h>
#include "sys.h"
#include "ErrorNumber.h"


/** Command_Handler.c **/
ErrorNumber_TypeDef Command_CurrPosSwitch(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_CurrentControlInputModify(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_PIDControlConfig(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_ReadCurrentOnly(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_Heartbeat(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_StartMeasurement(uint8_t *payload, uint8_t payload_len);
ErrorNumber_TypeDef Command_VoltRangeSwitch(uint8_t *payload, uint8_t payload_len);
bool Return_Direction(void);

#endif
