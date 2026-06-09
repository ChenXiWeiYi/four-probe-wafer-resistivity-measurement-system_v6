#include "GPIO_Init.h"

/**
 * @brief 两个LTC6373的增益
 *
 * LTC6373_1
 * A0:PG0  A1:PF14  A2:PF11
 *
 * LTC6373_2
 * A0:PG8  A1:PC7   A2:PC8
 *
 * LTC6373_3
 * A0:PC0  A1:PC3   A2:PC1
 *
 * !!!!!!!!!!!! 在2025.10.24时,控制信号是反向的 !!!!!!!!!!!!!!!!!!!
 *
 * @author 刘嘉诚
 * @date 2025.10.24
 */
void LTC6373_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

// LTC6373_1
	// A0
	GPIO_Initure.Pin	= GPIO_PIN_0;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;		// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	// A1 A2
	GPIO_Initure.Pin	= GPIO_PIN_11|GPIO_PIN_14;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;		// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);

// LTC6373_2
	// A0
	GPIO_Initure.Pin	= GPIO_PIN_8;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;		// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	// A1 A2
	GPIO_Initure.Pin	= GPIO_PIN_7|GPIO_PIN_8;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;		// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);


// LTC6373_3
	// A0 A1 A2
	GPIO_Initure.Pin	= GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;	// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;		// 下拉
	GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);

// 初始状态关断三个PGIA
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11|GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0|GPIO_PIN_8, GPIO_PIN_RESET);
}
