#include "GPIO_Init.h"

/**
 * @brief GPIO_Init
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void GPIO_Init(void)
{
	KeyBoardLED_GPIO_Init();
	KeyBoardKey_GPIO_Init();

	DAC_GPIO_Init();
	HC595_GPIO_Init();
	LTC6373_GPIO_Init();
	CCS2GND_GPIO_Init();
	ADC_GPIO_Init();
	MeasureDirection_GPIO_Init();

}
