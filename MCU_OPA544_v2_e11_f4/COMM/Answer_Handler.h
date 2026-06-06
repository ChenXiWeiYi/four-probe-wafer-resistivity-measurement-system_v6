#ifndef __ANSWER_HANDLER_H
#define __ANSWER_HANDLER_H

#include "sys.h"
#include "ErrorNumber.h"
#include <stdbool.h>

/** Answer_Handler.h **/
void Answer_Ack(uint8_t seq, uint8_t originCtrlByte);
void Answer_Nack(uint8_t seq, uint8_t originCtrlByte, ErrorNumber_TypeDef ErrorNumber);
void Answer_OperationDone(uint8_t seq, uint8_t originCtrlByte, ErrorNumber_TypeDef ErrorNumber);
void Answer_ChannelSwitchProgress(int CurrPos, int VoltRange, bool ok);
void Answer_MeasureComplete(void);
void Answer_VoltageCurrentUpdate(void);
void Answer_Error(ErrorNumber_TypeDef ErrorNumber);
void Answer_ReadCurrentOnly(void);
void Answer_CurrentForControl(void);

#endif
