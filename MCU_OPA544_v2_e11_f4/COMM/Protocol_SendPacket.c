#include "Protocol_USART.h"
#include "USART.h"

/**
 * 发送协议包通用函数
 * 参数:
 *   *payload: 你的数据内容
 *   payload_len: 载荷的长度
 */
void Protocol_SendPacket(uint8_t *payload, uint8_t payload_len)
{
    uint8_t tx_buffer[20];	// 20B的临时缓冲区,应该大概基本上是用不完的
    uint16_t crc;		// CRC的结果
    uint8_t crc_idx;	// CRC的坐标
    uint16_t total_frame_len;	// 从帧头到CRC的帧的总长度

    tx_buffer[0] = 0xAA;	// 帧头0xAA 0x55
    tx_buffer[1] = 0x55;

    tx_buffer[2] = payload_len + 2;	// 后面的数据+CRC的长度,不包括帧头和它自己

    if(payload_len > 0){
        memcpy(&tx_buffer[3], payload, payload_len);	// 把要发的存进去
    }

    // 5. 计算 CRC
    crc = Protocol_CalcCRC16(tx_buffer, 2 + 1 + payload_len);	// 帧头+"数据+CRC"长度+数据

    // 6. 填入 CRC (低位在前，高位在后)
    // 填在 Payload 的后面
    crc_idx = 3 + payload_len; // CRC开始的下标
    tx_buffer[crc_idx]     = (uint8_t)(crc & 0xFF);        // CRC Low
    tx_buffer[crc_idx + 1] = (uint8_t)((crc >> 8) & 0xFF); // CRC High

    // 7. 最终计算这帧的总长度
    // 头(2) + Len(1) + Payload + CRC(2)
    total_frame_len = 2 + 1 + payload_len + 2;	// 帧总长度

    // 8. 调用 HAL 库发送
    // 假设你用的是 UART1，如果是 UART2 请自行修改
    HAL_UART_Transmit(&USART1_Handler, tx_buffer, total_frame_len, 100);
}
