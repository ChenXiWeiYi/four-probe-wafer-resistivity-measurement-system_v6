#ifndef GLOBAL_ENUM_DEFINE_H
#define GLOBAL_ENUM_DEFINE_H

enum ParamName_TypeDef{
    NAME_Temperature = 0,
    NAME_SampleThickness = 1,
    NAME_SampleDiameter = 2,
    NAME_ProbeSpacing = 3,
    NAME_FspCorrectionFactor = 4,
    NAME_a = 5,
    NAME_b = 6,
    NAME_CurrErrorBound = 7,
    NAME_CurrPos = 8,
    NAME_VolRange = 9,
    NAME_SemiType = 10,
    NAME_MeasureMode = 11,
    NAME_ControlVoltages = 12,
    NAME_PID_Kp = 13,
    NAME_PID_Ti = 14,
    NAME_PID_Td = 15,
    NAME_PIDControlEnabled = 16
};

enum MeasureWarning_TypeDef{
    WARNING_UnderTemperature = 0
};

enum ValueType_TypeDef{
    VALUE_VOLTAGE = 0,
    VALUE_CURRENT = 1,
    VALUE_RESISTANCE = 2,
    VALUE_RESISTIVITY = 3,
    VALUE_SP_Current = 4,
    VALUE_Last_uk = 5,
    VALUE_delta_uk = 6,
    VALUE_Err = 7,
    VALUE_uk = 8
};

enum MeasureDirection_TypeDef{
    MEASUREDIRECTION_FORWARD = 0, // 正向
    MEASUREDIRECTION_REVERSE = 1  // 反向
};

enum CurrPos_TypeDef{
    CURRENTPOSITION_auto = 0,
    CURRENTPOSITION_100mA = 1,
    CURRENTPOSITION_25mA = 2,
    CURRENTPOSITION_2P5mA = 3,
    CURRENTPOSITION_250uA = 4,
    CURRENTPOSITION_25uA = 5,
    CURRENTPOSITION_2P5uA = 6,
    CURRENTPOSITION_250nA = 7
};

enum VolRange_TypeDef{
    VOLTAGERANGE_auto = 0,
    VOLTAGERANGE_300mV = 1,
    VOLTAGERANGE_30mV = 2,
    VOLTAGERANGE_3mV = 3
};

enum MeasureMode_TypeDef{
    MODE_SINGLE = 0,                    // 单组
    MODE_10TIMES_SINGLEPOINT_AUTO = 1,       // 单点测10组(自动)
    MODE_10TIMES_SINGLEPOINT_MAN = 2,   // 单点测10组(手动)
    MODE_10TIMES_MULTIPOINT_AUTO = 3,        // 多点测10组(自动)
    MODE_10TIMES_MULTIPOINT_MAN = 4     // 多点测10组(手动)
};

enum MeasureStage_TypeDef{
    STAGE_IDLE,                 // 空闲
    STAGE_MONITOR_CONTACT,      // 等待接触 (监控电流 > 0)
    STAGE_MEASURING,            // 正在正式测量
    STAGE_MONITOR_RELEASE       // 等待释放 (监控电流 ≈ 0)
};

enum SemiType_TypeDef{
    SEMITYPE_P = 0,
    SEMITYPE_N = 1
};

#endif // GLOBAL_ENUM_DEFINE_H
