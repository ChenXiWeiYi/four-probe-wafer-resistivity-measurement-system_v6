#include "EXTI_Init.h"

static volatile bool Flag_ADC2_DRDY = false;

/**
 * @brief EXTI4_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI4_Interrupt(void)
{
	Flag_ADC2_DRDY = true;
}

/**
 * @brief is_Flag_ADC2_DRDY
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool is_Flag_ADC2_DRDY(void)
{
	return Flag_ADC2_DRDY;
}

/**
 * @brief CLR_Flag_ADC2_DRDY
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void CLR_Flag_ADC2_DRDY(void)
{
	Flag_ADC2_DRDY = false;
}

