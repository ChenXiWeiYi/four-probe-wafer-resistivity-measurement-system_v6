#include "EXTI_Init.h"


void EXTI14_Interrupt(void)
{
//	LED1 = !LED1;
	LED4 = !LED4;
	LED5 = !LED5;
	LED3 = !LED3;
}

