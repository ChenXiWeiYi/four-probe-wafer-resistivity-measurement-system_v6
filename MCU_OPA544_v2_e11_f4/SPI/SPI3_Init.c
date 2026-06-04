#include "SPI_Init.h"

SPI_HandleTypeDef SPI3_Handler;

/**
 * @brief 用于ADC1210(ADC2)通讯
 *
 * ADS1210下降沿沿采样
 *
 * @date 2025.08.30
 */

void SPI3_Init(void)
{
	SPI3_Handler.Instance			= SPI3;
	SPI3_Handler.Init.Mode			= SPI_MODE_MASTER;		// 主模式
	SPI3_Handler.Init.Direction		= SPI_DIRECTION_2LINES;	// 双线模式
	SPI3_Handler.Init.DataSize		= SPI_DATASIZE_8BIT;	// 8位
	SPI3_Handler.Init.CLKPolarity	= SPI_POLARITY_LOW;		// 时钟空闲低电平
	SPI3_Handler.Init.CLKPhase		= SPI_PHASE_2EDGE;		// 第二个沿
	SPI3_Handler.Init.NSS			= SPI_NSS_SOFT;			// 内部软件NSS
	SPI3_Handler.Init.FirstBit		= SPI_FIRSTBIT_MSB;		// MSB开始传输
	SPI3_Handler.Init.TIMode		= SPI_TIMODE_DISABLE;	// 关闭TI模式
	SPI3_Handler.Init.CRCPolynomial	= 7;					// CRC多项式7
	SPI3_Handler.Init.CRCCalculation	= SPI_CRCCALCULATION_DISABLE;	// 不使用CRC
	SPI3_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;	// 256分频

	HAL_SPI_Init(&SPI3_Handler);
	__HAL_SPI_ENABLE(&SPI3_Handler);
}
