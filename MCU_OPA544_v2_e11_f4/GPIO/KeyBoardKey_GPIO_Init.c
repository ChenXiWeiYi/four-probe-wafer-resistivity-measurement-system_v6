#include "GPIO_Init.h"

/**
 * @brief 用于核心板按键管脚
 *
 * KEY1:PC6 KEY2:PC13 KEY3:PD14 KEY4:PE2
 *
 * @author 刘嘉诚
 * @date 2025.08.29
 */
void KeyBoardKey_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_Initure.Pin	= GPIO_PIN_6|GPIO_PIN_13;
	GPIO_Initure.Mode	= GPIO_MODE_IT_RISING;	// 外部中断,上升沿触发
	GPIO_Initure.Pull	= GPIO_NOPULL;			// 无上下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);

	GPIO_Initure.Pin	= GPIO_PIN_14;
	GPIO_Initure.Mode	= GPIO_MODE_IT_RISING;	// 外部中断,上升沿触发
	GPIO_Initure.Pull	= GPIO_NOPULL;			// 无上下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);

	GPIO_Initure.Pin	= GPIO_PIN_2;
	GPIO_Initure.Mode	= GPIO_MODE_IT_RISING;	// 外部中断,上升沿触发
	GPIO_Initure.Pull	= GPIO_NOPULL;			// 无上下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}
