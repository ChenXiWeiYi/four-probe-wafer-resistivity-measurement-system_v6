#include "SPI_Init.h"

void SPI_Init(void)
{
	SPI1_Init();
	SPI2_Init();
	SPI3_Init();
}



void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	__HAL_RCC_SPI1_CLK_ENABLE();
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_SPI3_CLK_ENABLE();

	if(hspi->Instance == SPI1)
	{
		GPIO_Initure.Pin		= GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
//		GPIO_Initure.Pin		= GPIO_PIN_5|GPIO_PIN_7;
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;			// 复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLDOWN;			// 下拉
		GPIO_Initure.Speed		= GPIO_SPEED_FREQ_HIGH;
		GPIO_Initure.Alternate	= GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	}

	if(hspi->Instance == SPI2)
	{
		GPIO_Initure.Pin		= GPIO_PIN_13|GPIO_PIN_15;
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;			// 复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLDOWN;			// 下拉
		GPIO_Initure.Speed		= GPIO_SPEED_FREQ_HIGH;
		GPIO_Initure.Alternate	= GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	}

	if(hspi->Instance == SPI3)
	{
		GPIO_Initure.Pin		= GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;			// 复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLDOWN;			// 下拉
		GPIO_Initure.Speed		= GPIO_SPEED_FREQ_HIGH;
		GPIO_Initure.Alternate	= GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	}
}
