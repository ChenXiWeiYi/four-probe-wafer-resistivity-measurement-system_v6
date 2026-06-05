#include "Control_Current_Value.h"
#include "Function_ADC.h"
#include "Function_DAC.h"
#include "Answer_Handler.h"

static bool Flag_PIDEnabled = false;
static bool Flag_PIDParamReceived = false;
static bool Flag_CurrentErrorReported = false;

static uint8_t CurrentPos_UI = 0;
static float SP_Current = 0.0f;
static float PV_Current = 0.0f;
static float Kp = 0.0f;
static float Ki = 0.0f;
static float Kd = 0.0f;
static float Last_uk = 0.0f;
static float Last_Err = 0.0f;
static float Last_Last_Err = 0.0f;
static float CurrErrorBoundPercent = 0.0f;

static float CurrentControl_ReturnCurrentGain(uint8_t currentPos)
{
    switch(currentPos){
    case 1: return 25.0f;
    case 2: return 100.0f;
    case 3: return 1000.0f;
    case 4: return 10000.0f;
    case 5: return 100000.0f;
    case 6: return 1000000.0f;
    case 7: return 1000000.0f;
    default: return 100000000000.0f;
    }
}

static float CurrentControl_Abs(float value)
{
    return value < 0.0f ? -value : value;
}

static float CurrentControl_LimitVoltage(float voltage)
{
    if(voltage > 3.0f) return 3.0f;
    if(voltage < 0.0f) return 0.0f;
    return voltage;
}

void CurrentControl_SetConfig(bool enabled, float errorBoundPercent)
{
    Flag_PIDEnabled = enabled;
    CurrErrorBoundPercent = errorBoundPercent;
    Flag_CurrentErrorReported = false;
}

void CurrentControl_SetEnabled(bool enabled)
{
    Flag_PIDEnabled = enabled;
    Flag_CurrentErrorReported = false;
}

void CurrentControl_SetParams(uint8_t currentPos, float spCurrent, float kp, float ki, float kd)
{
    CurrentPos_UI = currentPos;
    SP_Current = spCurrent;
    Kp = kp;
    Ki = ki;
    Kd = kd;
    Last_Err = 0.0f;
    Last_Last_Err = 0.0f;
    Flag_CurrentErrorReported = false;
    Flag_PIDParamReceived = true;
}

void CurrentControl_SetOutputVoltage(float voltage)
{
    Last_uk = CurrentControl_LimitVoltage(voltage);
}

float CurrentControl_ConvertADC2ToCurrent(void)
{
    float adcVoltage = Return_Data_ADC2_f();
    float currentGain = CurrentControl_ReturnCurrentGain(CurrentPos_UI);
    PV_Current = adcVoltage / currentGain;
    return PV_Current;
}

void CurrentControl_UpdateFromADC(void)
{
    float err;
    float errPercent;
    float deltaUk;
    float outputVoltage;

    CurrentControl_ConvertADC2ToCurrent();

    if(!Flag_PIDEnabled){
        return;
    }
    if(!Flag_PIDParamReceived){
        return;
    }
    if(SP_Current <= 0.0f){
        return;
    }

    err = SP_Current - PV_Current;
    errPercent = CurrentControl_Abs(err / SP_Current * 100.0f);

    if(CurrErrorBoundPercent > 0.0f && errPercent > CurrErrorBoundPercent){
        if(!Flag_CurrentErrorReported){
            Answer_Error(Error_CurrentOutOfRange);
            Flag_CurrentErrorReported = true;
        }
    }else{
        Flag_CurrentErrorReported = false;
    }

    if(Kp == 0.0f && Ki == 0.0f && Kd == 0.0f){
        return;
    }

    deltaUk = Kp * (err - Last_Err)
            + Ki * err
            + Kd * (err + Last_Last_Err - 2.0f * Last_Err);
    outputVoltage = CurrentControl_LimitVoltage(Last_uk + deltaUk);

    DAC_Write(outputVoltage);
    Last_uk = outputVoltage;
    Last_Last_Err = Last_Err;
    Last_Err = err;
}
