#include "Function_ADC.h"

void Set_ADC1_Gain(int num_Gain)
{
	uint8_t Ctrl_CMR2[2] = {0x05,0x00};
	// 可以考虑在这里加一个自检
	if((num_Gain < ADC_GAIN1) || (num_Gain > ADC_GAIN16))
	{
		// 报错
	}
	else
	{
		Ctrl_CMR2[1] = 0x00 + 4*(num_Gain-1);
	}
	HAL_SPI_Transmit(&SPI1_Handler, Ctrl_CMR2, 2, 100);
	delay_us(1);
}

/** 
 * @brief Set_ADC2_Gain 设置ADC2(电流测量)的增益
 * @date 2025.10.29
 */
void Set_ADC2_Gain(int num_Gain)
{
	uint8_t Ctrl_CMR2[2] = {0x05,0x00};
	// 可以考虑在这里加一个自检
	if((num_Gain < ADC_GAIN1) || (num_Gain > ADC_GAIN16))
	{
		// 报错
	}
	else
	{
		Ctrl_CMR2[1] = 0x00 + 4*(num_Gain-1);
	}
	HAL_SPI_Transmit(&SPI3_Handler, Ctrl_CMR2, 2, 100);
	delay_us(1);
}

