#include "EXTI_Init.h"
#include "Answer_Handler.h"
// KEY4
/**
 * @brief EXTI2_Interrupt
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void EXTI2_Interrupt(void)
{
	uint8_t Message;
	LED5 = !LED5;
//	Answer_MeasureComplete();
	Message = 0xE0;
	Protocol_SendPacket(&Message, 1);	
}
