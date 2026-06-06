#include "Command_Handler.h"
#include "Answer_Handler.h"
#include "Function_DAC.h"
#include "Channel_Switch.h"
#include "Measure.h"
#include "Control_Current_Value.h"
#include <string.h>

bool Flag_Direction = true;

static float PayloadToFloat(uint8_t *payload)
{
    float value = 0.0f;
    memcpy(&value, payload, 4);
    return value;
}

ErrorNumber_TypeDef Command_CurrPosSwitch(uint8_t *payload, uint8_t payload_len)
{
    uint8_t CurrPos;
    bool pidEnabled;
    float spCurrent;
    float kp;
    float ki;
    float kd;
    float initialUk;

    if(payload_len != 24){
        return Error_InvalidPayloadLength;
    }

    CurrPos = payload[2];
    if(CurrPos < 1 || CurrPos > 7){
        return Error_UnknownCurrentPosition;
    }

    if(payload[3] > 1){
        return Error_InvalidParameter;
    }

    pidEnabled = payload[3] ? true : false;
    spCurrent = PayloadToFloat(&payload[4]);
    kp = PayloadToFloat(&payload[8]);
    ki = PayloadToFloat(&payload[12]);
    kd = PayloadToFloat(&payload[16]);
    initialUk = PayloadToFloat(&payload[20]);

    if(initialUk < 0.0f || initialUk > 3.0f){
        return Error_InvalidParameter;
    }
    if(pidEnabled && spCurrent <= 0.0f){
        return Error_InvalidParameter;
    }
    if(is_CurrPosSwitch()){
        return Error_DeviceBusy;
    }

    Set_CurrentPositionDoneNotify(payload[1], payload[0]);
    Set_Current_Position((int)CurrPos);
    CurrentControl_SetEnabled(pidEnabled);
    CurrentControl_SetParams(CurrPos, spCurrent, kp, ki, kd, initialUk);
    DAC_Write(initialUk);

    return Error_None;
}

ErrorNumber_TypeDef Command_CurrentControlInputModify(uint8_t *payload, uint8_t payload_len)
{
    float SP_Current_f = 0.0f;

    if(payload_len != 6){
        return Error_InvalidPayloadLength;
    }

    memcpy(&SP_Current_f, &payload[2], 4);
    if(SP_Current_f < 0.0f || SP_Current_f > 3.0f){
        return Error_InvalidParameter;
    }

    DAC_Write(SP_Current_f);
    CurrentControl_SetOutputVoltage(SP_Current_f);

    return Error_None;
}

ErrorNumber_TypeDef Command_PIDControlConfig(uint8_t *payload, uint8_t payload_len)
{
    bool pidEnabled;
    float errorBound;

    if(payload_len != 7){
        return Error_PIDConfigLengthError;
    }

    if(payload[2] > 1){
        return Error_InvalidParameter;
    }

    pidEnabled = payload[2] ? true : false;
    errorBound = PayloadToFloat(&payload[3]);
    if(errorBound < 0.0f){
        return Error_InvalidParameter;
    }

    CurrentControl_SetConfig(pidEnabled, errorBound);

    return Error_None;
}

ErrorNumber_TypeDef Command_StartMeasurement(uint8_t *payload, uint8_t payload_len)
{
    uint8_t MeasureDirection;

    if(payload_len != 3){
        return Error_InvalidPayloadLength;
    }

    MeasureDirection = payload[2];
    if(MeasureDirection == 0x00){
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);
        LED2 = 0;
        Flag_Direction = true;
    }else if(MeasureDirection == 0xFF){
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_SET);
        LED2 = 1;
        Flag_Direction = false;
    }else{
        return Error_UnknownMeasureDirection;
    }
    Start_Measure();

    return Error_None;
}

ErrorNumber_TypeDef Command_ReadCurrentOnly(uint8_t *payload, uint8_t payload_len)
{
    if(payload_len != 2){
        return Error_InvalidPayloadLength;
    }

    Start_ReadCurrentOnly();

    return Error_None;
}

ErrorNumber_TypeDef Command_Heartbeat(uint8_t *payload, uint8_t payload_len)
{
    if(payload_len != 2){
        return Error_InvalidPayloadLength;
    }

    return Error_None;
}

ErrorNumber_TypeDef Command_VoltRangeSwitch(uint8_t *payload, uint8_t payload_len)
{
    int VolRange;

    if(payload_len != 3){
        return Error_InvalidPayloadLength;
    }

    VolRange = (int)payload[2];
    if(VolRange < 0 || VolRange > 3){
        return Error_VoltageRangeError;
    }

    if(VolRange != 0){
        Set_VoltMeter1_Range(VolRange);
    }

    return Error_None;
}

bool Return_Direction(void)
{
    return Flag_Direction;
}
