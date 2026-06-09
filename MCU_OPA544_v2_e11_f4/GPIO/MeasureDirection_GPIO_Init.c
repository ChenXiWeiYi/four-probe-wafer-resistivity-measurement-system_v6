#include "GPIO_Init.h"

/**
 * @brief 用于核心板LED管脚
 *
 * 1:PB11
 * 2:PE15
 * 3:PB10
 * 4:PE14
 *
 * @author 刘嘉诚
 * @date 2026.01.30
 */
void MeasureDirection_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_Initure.Pin	= GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;			// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	GPIO_Initure.Pin	= GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;			// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
//	SW_Probe_1 = 0;
}
