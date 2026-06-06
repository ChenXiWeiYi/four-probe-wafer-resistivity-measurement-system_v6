#ifndef GLOBAL_STRUCT_DEFINE_H
#define GLOBAL_STRUCT_DEFINE_H

#include "global_enum_define.h"
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QByteArray>

struct ParamStruct_TypeDef
{
    double Temperature = 23;
    double SampleThickness = 1;
    double SampleDiameter = 1;
    double ProbeSpacing = 1;
    double a = 1;
    double b = 0;
    double CurrErrorBound = 10;
    int CurrPos = 10;
    int VolRange = 10;
    double WS = 0;
    double SD = 0;
    double ThicknessCorrectionFactor = 1;
    double F2CorrectionFactor = 1;
    double FspCorrectionFactor = 1;
    double GeometryCorrectionFactor = 1;
    double TemperatureCorrectionFactor = 1;
    double CorrectionFactor = 1;
    SemiType_TypeDef SemiType = SEMITYPE_P;
    MeasureMode_TypeDef MeasureMode = MODE_SINGLE;
    QVector<float> ControlVoltages = QVector<float>(8, 0.0f);
    QVector<double> PID_Kp = QVector<double>(7, 750.0);
    QVector<double> PID_Ti = QVector<double>(7, 20.0);
    QVector<double> PID_Td = QVector<double>(7, 0.0);
    bool PIDControlEnabled = false;
};

struct MeasureValueStruct_TypeDef
{
    double Voltage;
    double Current;
    double Resistance;
    double Resistivity;
};

struct MeasureStateStruct_TypeDef
{
    MeasureDirection_TypeDef MeasureDirection = MEASUREDIRECTION_FORWARD;
    MeasureStage_TypeDef MeasureStage = STAGE_IDLE;
    int cnt_MeasureGroup = 0;
    int cnt_MeasureTimes = 0;
    QString Time_MeasurementStart = "Error_QAQ";
    bool Flag_TestCurrent = false;
    int cnt_Curr = 0;
    bool Flag_FirstReadCurrent = true;
};

struct CommStruct_TypeDef
{
    bool Flag_isWaitingEcho = false;
    bool Flag_isEchoVerified = false;
    QByteArray PayLoad_LastSend;
    unsigned char Seq_Next = 1;
    unsigned char Seq_Waiting = 0;
    unsigned char CtrlByte_Waiting = 0;
    unsigned char Error_LastAck = 0;
    bool Flag_isWaitingDone = false;
    unsigned char Seq_WaitingDone = 0;
    unsigned char CtrlByte_WaitingDone = 0;
    unsigned char Error_LastDone = 0;
};

struct ControllerStruct_TypeDef
{
    double SP_Current = 0.0025;
    double PV_Current = 0;
    double dt = 0.05;

    double Kp = 750.0;
    double Ti = 20;
    double Td = 0.0;
    double Err_Sum = 0.0;
    double Last_Err = 0.0;
    double Last_uk = 2.5;
    double Last_last_Err = 0;
};

#endif // GLOBAL_STRUCT_DEFINE_H
