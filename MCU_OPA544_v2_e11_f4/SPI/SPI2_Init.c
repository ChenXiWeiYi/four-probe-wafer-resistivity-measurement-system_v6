#include "SPI_Init.h"

SPI_HandleTypeDef SPI2_Handler;

/**
 * @brief 用于DAC8330通讯
 *
 * DAC8330上升沿采样
 *
 * @date 2025.08.30
 */

void SPI2_Init(void)
{
	SPI2_Handler.Instance			= SPI2;
	SPI2_Handler.Init.Mode			= SPI_MODE_MASTER;		// 主模式
	SPI2_Handler.Init.Direction		= SPI_DIRECTION_2LINES;	// 双线模式
	SPI2_Handler.Init.DataSize		= SPI_DATASIZE_8BIT;	// 8位
	SPI2_Handler.Init.CLKPolarity	= SPI_POLARITY_HIGH;		// 时钟空闲低电平
	SPI2_Handler.Init.CLKPhase		= SPI_PHASE_2EDGE;		// 第一个沿
	SPI2_Handler.Init.NSS			= SPI_NSS_SOFT;			// 内部软件NSS
	SPI2_Handler.Init.FirstBit		= SPI_FIRSTBIT_MSB;		// MSB开始传输
	SPI2_Handler.Init.TIMode		= SPI_TIMODE_DISABLE;	// 关闭TI模式
	SPI2_Handler.Init.CRCPolynomial	= 7;					// CRC多项式7
	SPI2_Handler.Init.CRCCalculation	= SPI_CRCCALCULATION_DISABLE;	// 不使用CRC
	SPI2_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;	// 256分频

	HAL_SPI_Init(&SPI2_Handler);
	__HAL_SPI_ENABLE(&SPI2_Handler);
}
