#include "Protocol_USART.h"

/**
 * 纯软件实现的 Modbus CRC16
 * 参数:
 *   *pData: 要计算的数据起始地址
 *   len:    要计算的字节数
 * 返回值:
 *   计算出的 16位 CRC
 */
uint16_t Protocol_CalcCRC16(uint8_t *pData, uint16_t len)
{
    uint16_t crc = 0xFFFF; // 初始值
    uint16_t poly = 0xA001; // 多项式
	uint16_t i;
	int	j;
    for(i = 0; i < len; i++){
        crc ^= pData[i];
        for(j = 0; j < 8; j++){
            if(crc & 1){
                crc >>= 1;
                crc ^= poly;
            }else{
                crc >>= 1;
            }
        }
    }
    return crc;
}
