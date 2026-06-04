#include "Function_DAC.h"

/**
 * DAC8830先写MSB
 *
 * @date 2025.08.30
 */
void DAC_Write(float Data_f)
{
	uint16_t	Data_u16 = 0;
	uint8_t		Data_u8[2] = {0};
	
	CS_DAC = 0;		// 启动
	delay_us(1);	// 最少10ns
	Data_u16 = (uint16_t)(Data_f / Data_FS_f * 65535);
	Data_u8[0] = (Data_u16 >> 8) & 0xFF;
	Data_u8[1] = Data_u16 & 0xFF;
#if 0	// 测试用1010 1010
	Data_u8[0] = 0xAA;
	Data_u8[1] = 0xAA;
#endif
	HAL_SPI_Transmit(&SPI2_Handler,Data_u8,2,100);
	delay_us(1);	// 最少10ns
	CS_DAC = 1;
	delay_us(1);	// 除极特殊情况,不要这个延迟都可以,保险
}
