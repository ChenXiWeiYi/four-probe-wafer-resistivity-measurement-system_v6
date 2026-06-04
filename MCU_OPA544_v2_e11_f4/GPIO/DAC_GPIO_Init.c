#include "GPIO_Init.h"

/**
 * @brief 提供恒流源参考电压输入的DAC
 *
 * DAC_DIN:PB15 DAC_SCLK:PB13 DAC_SYNC:PE8
 *
 * @date 2025.08.29
 */
void DAC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	__HAL_RCC_SPI2_CLK_ENABLE();

	// DIN SCLK
		// 在SPI_Init.c中配置
	// SYNC
	GPIO_Initure.Pin	= GPIO_PIN_8;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;				// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
}
