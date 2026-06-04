#include "Function_ADC.h"

static bool Flag_ADC1_ReadComplete = false;
static bool Flag_ADC2_ReadComplete = false;
static int	delay_time = 5;	// 最小5.5*0.1 us

uint8_t	Data_ADC1_u8[SIZE_Data_ADC] = {0x3F, 0xFF, 0xFF};
uint8_t	Data_ADC2_u8[SIZE_Data_ADC] = {0x3F, 0xFF, 0xFF};

#if 1
/** 
 * @author	刘嘉诚
 * @date	2025.08.30 
 */
void ADC1_Read(void)
{
	uint8_t DOR_INSR = 0xC0;	// DOR2,1100 0000,读,3B
	uint8_t DOR_Data[SIZE_Data_ADC] = {0x3F, 0xFF, 0xFF};
	HAL_SPI_Transmit(&SPI1_Handler, &DOR_INSR, 1, 100);
	delay_us(1);
	HAL_SPI_Receive(&SPI1_Handler, DOR_Data, SIZE_Data_ADC, 100);
	delay_us(delay_time);
	memcpy(Data_ADC1_u8, DOR_Data, SIZE_Data_ADC);
	Flag_ADC1_ReadComplete = true;
}
#endif



/** 
 * @author	刘嘉诚
 * @date	2025.08.30 
 */
void ADC2_Read(void)
{
	uint8_t DOR_INSR = 0xC0;	// DOR2,1100 0000,读,3B
	uint8_t DOR_Data[SIZE_Data_ADC] = {0x3F, 0xFF, 0xFF};
	HAL_SPI_Transmit(&SPI3_Handler, &DOR_INSR, 1, 100);
	delay_us(delay_time);
	HAL_SPI_Receive(&SPI3_Handler, DOR_Data, SIZE_Data_ADC, 100);
	delay_us(delay_time);
	memcpy(Data_ADC2_u8, DOR_Data, SIZE_Data_ADC);
	Flag_ADC2_ReadComplete = true;
}


/** 
 * @author	刘嘉诚
 * @date	2025.09.01 
 */
bool is_ADC1_ReadComplete(void)
{
	return Flag_ADC1_ReadComplete;
}


/** 
 * @author	刘嘉诚
 * @date	2025.09.01 
 */
bool is_ADC2_ReadComplete(void)
{
	return Flag_ADC2_ReadComplete;
}


/**
 * @brief	ADC1测量值转成float
 *
 * @return	浮点数ADC1测量值
 * @author	刘嘉诚
 * @date	2025.10.24
 */
float Return_Data_ADC1_f(void)
{
	uint32_t	Data_ADC1_u32 = 0;
	float		Data_ADC1_f = 0;

	Data_ADC1_u32 = ((uint32_t)Data_ADC1_u8[0] << 16) | ((uint32_t)Data_ADC1_u8[1] << 8) | ((uint32_t)Data_ADC1_u8[2]);
	Data_ADC1_f = (float)Data_ADC1_u32 / 8388607 * 5;	// 8388607=7FFFFFH-0; 5为ADC的VAA
	return Data_ADC1_f;
}


/**
 * @brief	ADC2测量值转成float
 *
 * @return	浮点数ADC2测量值
 * @author	刘嘉诚
 * @date	2025.10.24
 */
float Return_Data_ADC2_f(void)
{
	uint32_t	Data_ADC2_u32 = 0;
	float		Data_ADC2_f = 0;

	Data_ADC2_u32 = ((uint32_t)Data_ADC2_u8[0] << 16) | ((uint32_t)Data_ADC2_u8[1] << 8) | ((uint32_t)Data_ADC2_u8[2]);
	Data_ADC2_f = (float)Data_ADC2_u32 / 8388607 * 5;	// 8388607=7FFFFFH-0; 5为ADC的VAA
	return Data_ADC2_f;
}
