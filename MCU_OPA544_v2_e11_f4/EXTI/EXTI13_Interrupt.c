#include "EXTI_Init.h"
#include "Function_ADC.h"

/**
 * @brief EXTI13_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI13_Interrupt(void)
{
	LED1 = !LED1;
	SW_Probe_1 = !SW_Probe_1;
	
}
