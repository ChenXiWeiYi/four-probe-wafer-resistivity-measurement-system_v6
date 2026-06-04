#include "Protocol_USART.h"
#include "USART.h"
#include "Command_Handler.h"
#include "Answer_Handler.h"

/**
 * @brief Process_USART1 USART1的接收帧处理
 * @date 2026.02.03
 */
void Process_USART1(void)
{
	uint16_t calCRC;	// CRC校验结果
	uint16_t recCRC;	// 接收到的CRC
	uint8_t CtrlByte;	// 控制字,其实不用定义,单纯地为了方便理解
	uint8_t payload_len = RxPacketLen - 5;
	uint8_t *pPayload = &RxPacket[3];
	
	calCRC = Protocol_CalcCRC16(RxPacket, RxPacketLen - 2);
	recCRC = (RxPacket[RxPacketLen-1] << 8) | RxPacket[RxPacketLen-2];
	
	if(calCRC == recCRC){
		CtrlByte = RxPacket[3];
		switch(CtrlByte & 0xF0){
		case(0x10):	// 控制各种模式
//			Control_Mode(CtrlByte); 2026.02.03 废弃
			break;
		case(0x20):	// 切换通道
			Command_CurrPosSwitch(CtrlByte);
			break;
		case(0x30):	// 读取电压
//			Control_VoltageUpload(); 2026.02.03 废弃
			break;
		case(0x40):	// 读取电流
			Command_ReadCurrentOnly();
			break;
		case(0x50):	// 读取电压电流
//			Control_VoltageCurrentUpload(); 2026.02.03 废弃
			break;
		case(0x60):	// 切换电压档位
			Command_VoltRangeSwitch(CtrlByte);
			break;
		case(0xA0):	// 设置压控输入
			Command_CurrentControlInputModify(&RxPacket[4]);
			break;
		case(0xB0): // 开始测量
			Command_StartMeasurement(RxPacket[4]);
			break;
		case(0xE0):	// 档位选取
			break;
		default:
			Answer_Error(Error_UnknownOperation);	// 发送错误信息
			break;
		}
		Protocol_SendPacket(pPayload, payload_len);
	}else{
		Answer_Error(Error_CRCError);
	}
	USART1_Clear_Rx();	// 清空USART1的接收标志位
}
