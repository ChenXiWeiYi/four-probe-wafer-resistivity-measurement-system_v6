#ifndef GLOBAL_STRUCT_DEFINE_H
#define GLOBAL_STRUCT_DEFINE_H

#include "global_enum_define.h"
#include <QString>
#include <QDateTime>
#include <QVector>

struct ParamStruct_TypeDef
{
    double Temperature = 23;    // 温度
    double SampleThickness = 1; // 样品厚度
    double SampleDiameter = 1;  // 样品直径
    double ProbeSpacing = 1;    // 探针间距
    double a = 1;       // 两点校正a
    double b = 0;       // 两点校正b
    double CurrErrorBound = 10; // 电流误差限
    int CurrPos = 10;   // 电流档位
    int VolRange = 10;  // 电压档位
    double WS = 0;      // 样品厚度与探针间距之比
    double SD = 0;      // 探针间距与样品直径之比
    double ThicknessCorrectionFactor = 1;   // 样品厚度修正因子
    double F2CorrectionFactor = 1;  // 样品直径修正因子
    double FspCorrectionFactor = 1; // 探针校正因子
    double GeometryCorrectionFactor = 1;    // 几何修正因子
    double TemperatureCorrectionFactor = 1; // 温度修正因子
    double CorrectionFactor = 1;    // 修正因子
    SemiType_TypeDef SemiType = SEMITYPE_P;
    MeasureMode_TypeDef MeasureMode = MODE_SINGLE;  // 测量方法
    QVector<float> ControlVoltages = QVector<float>(8, 0.0f);
    ControlAlgo_TypeDef ControlAlgo = ALGO_NONE;


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
    MeasureDirection_TypeDef MeasureDirection = MEASUREDIRECTION_FORWARD;   // 测量方向
    MeasureStage_TypeDef MeasureStage = STAGE_IDLE;
    int cnt_MeasureGroup = 0;   // 测量组数
    int cnt_MeasureTimes = 0;   // 测量次数
    QString Time_MeasurementStart = "错误哦QAQ";   // 测量时间
    bool Flag_TestCurrent = false;
    int cnt_Curr = 0;

    bool Flag_FirstReadCurrent = true;
};

struct CommStruct_TypeDef
{
    bool Flag_isWaitingEcho = false;
    bool Flag_isEchoVerified = false;
    QByteArray PayLoad_LastSend;
};

struct ControllerStruct_TypeDef {
    ControlAlgo_TypeDef AlgoType = ALGO_NORMAL_PID; // 当前选择的算法

    double SP_Current = 0.0025; // 目标给定量 (Setpoint) - 比如 2.5mA就是 0.0025A
    double PV_Current = 0;
    double dt = 0.05;           // 控制周期 (秒) - 比如50ms定时器就是 0.05s

    // ======== PID 参数 ========
    double Kp = 750.0;
    double Ti = 20;          // 积分时间
    double Td = 0.0;            // 微分时间
    double T_lambda = 10;
    double K_lambda = 100;
    double Tao_lambda = 1;
    double Lambda_lambda = 1;
    double Err_Sum = 0.0;       // 积分累加
    double Last_Err = 0.0;      // 上次误差 (用于微分)
    double Last_uk = 2.5;
    double Last_last_Err = 0;

    // ======== MPC 参数 ========
    double model_a = 0.8;       // 一阶离散模型参数a (需要后续测定)
    double model_b = 0.5;       // 一阶离散模型参数b (需要后续测定)
    double MPC_Err_Sum = 0.0;   // MPC稳态误差消除项
    double R_Weight = 0.1;
};

#endif // GLOBAL_STRUCT_DEFINE_H


