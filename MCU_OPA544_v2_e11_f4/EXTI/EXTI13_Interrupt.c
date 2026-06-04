#include "EXTI_Init.h"
#include "Function_ADC.h"

void EXTI13_Interrupt(void)
{
	LED1 = !LED1;
	SW_Probe_1 = !SW_Probe_1;
	
}
