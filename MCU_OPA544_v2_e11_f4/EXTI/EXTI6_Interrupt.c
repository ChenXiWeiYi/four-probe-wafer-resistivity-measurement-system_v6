#include "EXTI_Init.h"

void EXTI6_Interrupt(void)
{
	CCS_GND = !CCS_GND;
	LED2 = !LED2;
}
