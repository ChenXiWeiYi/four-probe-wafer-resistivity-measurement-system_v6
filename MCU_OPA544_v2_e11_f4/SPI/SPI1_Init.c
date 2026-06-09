#include "SPI_Init.h"

SPI_HandleTypeDef SPI1_Handler;

/**
 * @brief 用于ADC1210(ADC1)通讯
 *
 * ADS1210下降沿沿采样
 *
 * @author 刘嘉诚
 * @date 2025.08.30
 */

void SPI1_Init(void)
{
	SPI1_Handler.Instance			= SPI1;
	SPI1_Handler.Init.Mode			= SPI_MODE_MASTER;		// 主模式
	SPI1_Handler.Init.Direction		= SPI_DIRECTION_2LINES;	// 双线模式
	SPI1_Handler.Init.DataSize		= SPI_DATASIZE_8BIT;	// 8位
	SPI1_Handler.Init.CLKPolarity	= SPI_POLARITY_LOW;		// 时钟空闲低电平
	SPI1_Handler.Init.CLKPhase		= SPI_PHASE_2EDGE;		// 第二个沿
	SPI1_Handler.Init.NSS			= SPI_NSS_SOFT;			// 内部软件NSS
	SPI1_Handler.Init.FirstBit		= SPI_FIRSTBIT_MSB;		// MSB开始传输
	SPI1_Handler.Init.TIMode		= SPI_TIMODE_DISABLE;	// 关闭TI模式
	SPI1_Handler.Init.CRCPolynomial	= 7;					// CRC多项式7
	SPI1_Handler.Init.CRCCalculation	= SPI_CRCCALCULATION_DISABLE;	// 不使用CRC
	SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;	// 256分频

	HAL_SPI_Init(&SPI1_Handler);
	__HAL_SPI_ENABLE(&SPI1_Handler);
}
