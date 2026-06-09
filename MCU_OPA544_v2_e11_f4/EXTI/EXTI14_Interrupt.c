#include "EXTI_Init.h"


/**
 * @brief EXTI14_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI14_Interrupt(void)
{
//	LED1 = !LED1;
	LED4 = !LED4;
	LED5 = !LED5;
	LED3 = !LED3;
}

