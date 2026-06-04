#include "EXTI_Init.h"

static bool Flag_ADC2_DRDY = false;

void EXTI4_Interrupt(void)
{
	Flag_ADC2_DRDY = true;
}

bool is_Flag_ADC2_DRDY(void)
{
	return Flag_ADC2_DRDY;
}

void CLR_Flag_ADC2_DRDY(void)
{
	Flag_ADC2_DRDY = false;
}

