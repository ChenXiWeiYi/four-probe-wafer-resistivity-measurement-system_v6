#include "GPIO_Init.h"

/**
 * @brief 用于核心板LED管脚
 *
 * LED1:PF8 LED2:PF6 LED3:PF4 LED4:PF2 LED5:PF0
 *
 * @date 2025.08.29
 */
void KeyBoardLED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOF_CLK_ENABLE();

	GPIO_Initure.Pin	= GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;			// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);

	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 1;
}
