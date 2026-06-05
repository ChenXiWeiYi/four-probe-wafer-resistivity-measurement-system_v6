#ifndef __USART_H
#define __USART_H

#include "sys.h"
#include <stdbool.h>
#include <stdio.h>

/** 预编译 **/
#define PROTOCOL_HEAD1	0xAA	// 帧头1
#define PROTOCOL_HEAD2	0x55	// 帧头2
#define MAX_RX_LEN		64		// 最大接收缓冲区大小(根据实际需求调整)

/** 接收状态机枚举 **/
typedef enum {
    RX_STATE_WAIT_HEAD1 = 0,    // 等待帧头1 (AA)
    RX_STATE_WAIT_HEAD2,        // 等待帧头2 (55)
    RX_STATE_WAIT_LEN,          // 等待长度字节
    RX_STATE_WAIT_BODY,         // 等待数据体 (Payload + CRC)
    RX_STATE_COMPLETE           // (内部状态) 接收完成
} RxState_t;

/** 全局变量声明 **/
extern UART_HandleTypeDef USART1_Handler;
extern uint8_t  RxPacket[MAX_RX_LEN];   // 接收到的完整数据包
extern uint16_t RxPacketLen;            // 当前包的总长度

/** 函数声明 **/
/******** USART.c ********/
void USART_Init(uint32_t BaudRate_USART1);
void USART1_Clear_Rx(void);              // 清除接收标志，准备下一次接收
bool is_USART1_RxOK(void);              // 查询是否接收完成

#endif
