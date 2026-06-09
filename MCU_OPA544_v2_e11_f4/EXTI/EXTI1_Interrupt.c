#include "EXTI_Init.h"

static volatile bool Flag_ADC1_DRDY = false;
static int cnt = 0;
/**
 * @brief EXTI1_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI1_Interrupt(void)
{
	Flag_ADC1_DRDY = true;
	if(cnt == 100)
	{
		LED3 = !LED3;
	}else
	{
		cnt = cnt + 1;
	}
}

/**
 * @brief is_Flag_ADC1_DRDY
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool is_Flag_ADC1_DRDY(void)
{
	return Flag_ADC1_DRDY;
}

/**
 * @brief CLR_Flag_ADC1_DRDY
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void CLR_Flag_ADC1_DRDY(void)
{
	Flag_ADC1_DRDY = false;
}
