#include "GPIO_Init.h"

/**
 * @brief ADC_GPIO_Init 配置两个ADS1210管脚
 *
 * ADC1
 * SCK:PA5	SDOUT:PA6	SDIO:PA7
 * CS:PA3	DRDY:PB1	DSYNC:PA4
 *
 * ADC2
 * SCK:PC10	SDOUT:PC11	SDIO:PC12
 * CS:PD1	DRDY:PD4	DSYNC:PD0
 *
 * @date 2025.08.29
 */
void ADC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
//	__HAL_RCC_GPIOC_CLK_ENABLE();	(2025.09.04 在SPI_Init里了)
	__HAL_RCC_GPIOD_CLK_ENABLE();

// ADC1
	// SCK SDIO SDOUT
		// 在SPI_Init.c中配置
	// CS DSYNC
	GPIO_Initure.Pin	= GPIO_PIN_3|GPIO_PIN_4;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;			// 下拉
    GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	// DRDY
	GPIO_Initure.Pin	= GPIO_PIN_1;
	GPIO_Initure.Mode	= GPIO_MODE_IT_FALLING;		// 外部中断,下升沿触发
	GPIO_Initure.Pull	= GPIO_PULLDOWN;				// 下拉
    GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);


// ADC2
	// SCK SDIO SDOUT
		// 在SPI_Init.c中配置
	// CS DSYNC
	GPIO_Initure.Pin	= GPIO_PIN_0|GPIO_PIN_1;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;		// 推挽输出
	GPIO_Initure.Pull	= GPIO_PULLDOWN;			// 下拉
    GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	// DRDY
	GPIO_Initure.Pin	= GPIO_PIN_4;
	GPIO_Initure.Mode	= GPIO_MODE_IT_FALLING;		// 外部中断,下升沿触发
	GPIO_Initure.Pull	= GPIO_PULLDOWN;				// 下拉
    GPIO_Initure.Speed	= GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

}
