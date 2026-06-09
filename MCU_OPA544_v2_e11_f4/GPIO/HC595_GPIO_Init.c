#include "GPIO_Init.h"

/**
 * @brief 用于恒流源通道切换的74HC595管脚
 *
 * DS:PC2	OE:PF9	MR:PA2
 * STCP:PF7	SHCP:PA1
 *
 * @author 刘嘉诚
 * @date 2025.08.29
 */
void HC595_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

// MR SHCP
	GPIO_Initure.Pin	= GPIO_PIN_1|GPIO_PIN_2;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLUP;				// 上拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;		// 高速
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);
// DS
	GPIO_Initure.Pin	= GPIO_PIN_2;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLUP;				// 上拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;		// 高速
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);
// OE STCP
	GPIO_Initure.Pin	= GPIO_PIN_7|GPIO_PIN_9;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLUP;				// 上拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;		// 高速
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);

	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);	//初始状态74HC595不使能
}
