#include "Protocol_USART.h"
#include "USART.h"
#include "Command_Handler.h"
#include "Answer_Handler.h"

/**
 * @brief Process_USART1
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Process_USART1(void)
{
    uint16_t calCRC;
    uint16_t recCRC;
    uint8_t CtrlByte;
    uint8_t Seq;
    ErrorNumber_TypeDef commandResult;
    uint8_t payload_len = RxPacketLen - 5;
    uint8_t *pPayload = &RxPacket[3];

    calCRC = Protocol_CalcCRC16(RxPacket, RxPacketLen - 2);
    recCRC = (RxPacket[RxPacketLen - 1] << 8) | RxPacket[RxPacketLen - 2];

    if(calCRC == recCRC){
        if(payload_len < 2){
            Answer_Error(Error_InvalidPayloadLength);
            USART1_Clear_Rx();
            return;
        }

        CtrlByte = RxPacket[3];
        Seq = RxPacket[4];
        commandResult = Error_UnknownOperation;

        switch(CtrlByte){
        case 0x20:
            commandResult = Command_CurrPosSwitch(pPayload, payload_len);
            break;
        case 0x40:
            commandResult = Command_ReadCurrentOnly(pPayload, payload_len);
            break;
        case 0x60:
            commandResult = Command_VoltRangeSwitch(pPayload, payload_len);
            break;
        case 0x70:
            commandResult = Command_Heartbeat(pPayload, payload_len);
            break;
        case 0xA0:
            commandResult = Command_CurrentControlInputModify(pPayload, payload_len);
            break;
        case 0xB0:
            commandResult = Command_StartMeasurement(pPayload, payload_len);
            break;
        case 0xC0:
            commandResult = Command_PIDControlConfig(pPayload, payload_len);
            break;
        case 0xE0:
            commandResult = Error_None;
            break;
        default:
            commandResult = Error_UnknownOperation;
            break;
        }

        if(commandResult == Error_None){
            Answer_Ack(Seq, CtrlByte);
        }else{
            Answer_Nack(Seq, CtrlByte, commandResult);
        }
    }else{
        Answer_Error(Error_CRCError);
    }
    USART1_Clear_Rx();
}
