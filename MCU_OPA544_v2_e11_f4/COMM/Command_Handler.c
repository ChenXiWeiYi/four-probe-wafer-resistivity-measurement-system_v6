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

void Command_CurrPosSwitch(uint8_t *payload, uint8_t payload_len)
{
    uint8_t CtrlByte;
    uint8_t CurrPos;
    uint8_t uiCurrPos;
    bool pidEnabled;
    float spCurrent;
    float kp;
    float ki;
    float kd;

    CtrlByte = payload[0];
    CurrPos = CtrlByte & 0x0F;
    Set_Current_Position((int)CurrPos);

    if(payload_len >= 19){
        uiCurrPos = payload[1];
        pidEnabled = payload[2] ? true : false;
        spCurrent = PayloadToFloat(&payload[3]);
        kp = PayloadToFloat(&payload[7]);
        ki = PayloadToFloat(&payload[11]);
        kd = PayloadToFloat(&payload[15]);

        CurrentControl_SetEnabled(pidEnabled);
        CurrentControl_SetParams(uiCurrPos, spCurrent, kp, ki, kd);
    }
}

void Command_CurrentControlInputModify(uint8_t *p_SP_Current_u8)
{
    float SP_Current_f = 0.0f;
    memcpy(&SP_Current_f, p_SP_Current_u8, 4);
    DAC_Write(SP_Current_f);
    CurrentControl_SetOutputVoltage(SP_Current_f);
}

void Command_PIDControlConfig(uint8_t *payload, uint8_t payload_len)
{
    bool pidEnabled;
    float errorBound;

    if(payload_len < 6){
        Answer_Error(Error_PIDConfigLengthError);
        return;
    }

    pidEnabled = payload[1] ? true : false;
    errorBound = PayloadToFloat(&payload[2]);
    CurrentControl_SetConfig(pidEnabled, errorBound);
}

void Command_StartMeasurement(uint8_t MeasureDirection)
{
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
        Answer_Error(Error_UnknownMeasureDirection);
    }
    Start_Measure();
}

void Command_ReadCurrentOnly(void)
{
    Start_ReadCurrentOnly();
}

void Command_VoltRangeSwitch(uint8_t CtrlByte)
{
    int VolRange = (int)(CtrlByte & 0x0F);

    if((VolRange < 0) || (VolRange > 3)){
        Answer_Error(Error_VoltageRangeError);
    }else{
        if(VolRange != 0){
            Set_VoltMeter1_Range(VolRange);
        }
    }
}

bool Return_Direction(void)
{
    return Flag_Direction;
}
