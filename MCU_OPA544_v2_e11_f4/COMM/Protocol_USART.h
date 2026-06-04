#ifndef Protocol_USART_H
#define Protocol_USART_H

#include "sys.h"

/**   Protocol_SendPacket.c   **/
void Protocol_SendPacket(uint8_t *payload, uint8_t payload_len);

/**   Protocol_CalCRC16.c   **/
uint16_t Protocol_CalcCRC16(uint8_t *pData, uint16_t len);

/** Process_USART1.c **/
void Process_USART1(void);

#endif
