#include "EXTI_Init.h"

static bool Flag_ADC1_DRDY = false;
static int cnt = 0;
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

bool is_Flag_ADC1_DRDY(void)
{
	return Flag_ADC1_DRDY;
}

void CLR_Flag_ADC1_DRDY(void)
{
	Flag_ADC1_DRDY = false;
}
