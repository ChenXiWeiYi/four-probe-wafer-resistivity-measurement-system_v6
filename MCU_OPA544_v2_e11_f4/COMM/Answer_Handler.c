#include "Answer_Handler.h"
#include "Command_Handler.h"
#include "Protocol_USART.h"
#include "Function_ADC.h"
#include <string.h>

void Answer_Ack(uint8_t seq, uint8_t originCtrlByte)
{
	uint8_t Message[5] = {0x10, 0x00, 0x00, 0x00, Error_None};
	Message[1] = seq;
	Message[2] = originCtrlByte;
	Protocol_SendPacket(&Message[0], sizeof(Message));
}

void Answer_Nack(uint8_t seq, uint8_t originCtrlByte, ErrorNumber_TypeDef ErrorNumber)
{
	uint8_t Message[5] = {0x10, 0x00, 0x00, 0x01, Error_UnknownOperation};
	Message[1] = seq;
	Message[2] = originCtrlByte;
	Message[4] = ErrorNumber;
	Protocol_SendPacket(&Message[0], sizeof(Message));
}

/**
 * @brief Send operation completion frame 0x30.
 * @param seq Command sequence copied from original command.
 * @param originCtrlByte Original command control byte.
 * @param ErrorNumber Completion result error code.
 */
void Answer_OperationDone(uint8_t seq, uint8_t originCtrlByte, ErrorNumber_TypeDef ErrorNumber)
{
	uint8_t Message[5] = {0x30, 0x00, 0x00, 0x00, Error_None};
	Message[1] = seq;
	Message[2] = originCtrlByte;
	if(ErrorNumber != Error_None){
		Message[3] = 0x01;
		Message[4] = ErrorNumber;
	}
	Protocol_SendPacket(&Message[0], sizeof(Message));
}

void Answer_ChannelSwitchProgress(int CurrPos, int VoltRange, bool ok)
{
	uint8_t Message[2] = {0xE0, 0x00};
	if(ok){
		Message[0] = 0xEF;
	}else{
		Message[0] = 0xE0;
	}
	Message[1] = (((uint8_t)VoltRange & 0x0F) << 4) | ((uint8_t)(CurrPos & 0x0F));
	Protocol_SendPacket(&Message[0], sizeof(Message));	
}

/**
 * @brief Answer_MeasureComplete 答复:测量完成
 * @date 2026.02.03
 */
void Answer_MeasureComplete(void)
{
	uint8_t Message[2] = {0xB0,0x12};
	if(Return_Direction() == true){
		Message[1] = 0x55;
	}else{
		Message[1] = 0xAA;
	}
	Protocol_SendPacket(&Message[0], 2);	
}

/**
 * @brief Answer_VoltageCurrentUpdate 答复:电压电流测量ADC输出值
 * @date 2026.02.03
 */
void Answer_VoltageCurrentUpdate(void)
{
	uint8_t	Message[7] = {0x50,0x01,0x23,0x45,0x67,0x78,0x9A};
	memcpy(&Message[1], Data_ADC1_u8, SIZE_Data_ADC);
	memcpy(&Message[4], Data_ADC2_u8, SIZE_Data_ADC);
#if 0	// 测试用
	Message[1] = 0x7F;
	Message[2] = 0xFF;
	Message[3] = 0xFF;
#endif 
	Protocol_SendPacket(&Message[0], sizeof(Message));	
}

/**
 * @brief Answer_Error 答复:错误
 * @param ErrorNumber 错误编号
 * @date 2026.02.03
 */
void Answer_Error(ErrorNumber_TypeDef ErrorNumber)
{
	uint8_t Message[2] = {0xF0, 0xFF};
	Message[1] = ErrorNumber;
	Protocol_SendPacket(&Message[0], 2);
}


void Answer_ReadCurrentOnly(void)
{
	uint8_t	Message[4] = {0x40,0x01,0x23,0x45};
	memcpy(&Message[1], Data_ADC2_u8, SIZE_Data_ADC);
#if 0	// 测试用
	Message[1] = 0x7F;
	Message[2] = 0xFF;
	Message[3] = 0xFF;
#endif 
	Protocol_SendPacket(&Message[0], sizeof(Message));	
}

/**
 * @brief Answer_CurrentForControl 答复:用于控制的电流读取
 * @date 2026.03.11
 */
void Answer_CurrentForControl(void)
{
	uint8_t	Message[4] = {0xD0,0x01,0x23,0x45};
	memcpy(&Message[1], Data_ADC2_u8, SIZE_Data_ADC);
#if 0	// 测试用
	Message[1] = 0x7F;
	Message[2] = 0xFF;
	Message[3] = 0xFF;
#endif 
	Protocol_SendPacket(&Message[0], sizeof(Message));	
}
