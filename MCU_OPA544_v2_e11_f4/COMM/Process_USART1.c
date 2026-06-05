#include "Protocol_USART.h"
#include "USART.h"
#include "Command_Handler.h"
#include "Answer_Handler.h"

void Process_USART1(void)
{
    uint16_t calCRC;
    uint16_t recCRC;
    uint8_t CtrlByte;
    uint8_t payload_len = RxPacketLen - 5;
    uint8_t *pPayload = &RxPacket[3];

    calCRC = Protocol_CalcCRC16(RxPacket, RxPacketLen - 2);
    recCRC = (RxPacket[RxPacketLen - 1] << 8) | RxPacket[RxPacketLen - 2];

    if(calCRC == recCRC){
        CtrlByte = RxPacket[3];
        switch(CtrlByte & 0xF0){
        case 0x20:
            Command_CurrPosSwitch(pPayload, payload_len);
            break;
        case 0x40:
            Command_ReadCurrentOnly();
            break;
        case 0x60:
            Command_VoltRangeSwitch(CtrlByte);
            break;
        case 0xA0:
            Command_CurrentControlInputModify(&RxPacket[4]);
            break;
        case 0xB0:
            Command_StartMeasurement(RxPacket[4]);
            break;
        case 0xC0:
            Command_PIDControlConfig(pPayload, payload_len);
            break;
        case 0xE0:
            break;
        default:
            Answer_Error(Error_UnknownOperation);
            break;
        }
        Protocol_SendPacket(pPayload, payload_len);
    }else{
        Answer_Error(Error_CRCError);
    }
    USART1_Clear_Rx();
}
