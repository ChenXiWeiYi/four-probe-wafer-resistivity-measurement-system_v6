#include "EXTI_Init.h"

/**
 * @brief EXTI6_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI6_Interrupt(void)
{
	CCS_GND = !CCS_GND;
	LED2 = !LED2;
}
