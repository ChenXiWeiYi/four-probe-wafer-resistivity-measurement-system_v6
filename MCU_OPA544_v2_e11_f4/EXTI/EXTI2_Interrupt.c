#include "EXTI_Init.h"
#include "Answer_Handler.h"
// KEY4
void EXTI2_Interrupt(void)
{
	uint8_t Message;
	LED5 = !LED5;
//	Answer_MeasureComplete();
	Message = 0xE0;
	Protocol_SendPacket(&Message, 1);	
}
