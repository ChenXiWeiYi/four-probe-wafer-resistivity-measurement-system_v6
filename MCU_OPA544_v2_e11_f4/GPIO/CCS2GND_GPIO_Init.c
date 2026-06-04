#include "GPIO_Init.h"

/**
 * @brief 用于控制恒流源输出接地继电器
 *
 * CCS_GND:PB0
 *
 * @date 2025.08.29
 */

void CCS2GND_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_Initure.Pin	= GPIO_PIN_0;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLUP;			// 上拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);	// 初始状态继电器闭合
}
