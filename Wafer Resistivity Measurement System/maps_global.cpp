#include "global_maps.h"

const QMap<CurrPos_TypeDef, QString> Map_CurrPos = {
    { CURRENTPOSITION_auto,     "自动" },
    { CURRENTPOSITION_100mA,    "100mA" },
    { CURRENTPOSITION_25mA,     "25mA" },
    { CURRENTPOSITION_2P5mA,    "2.5mA" },
    { CURRENTPOSITION_250uA,    "250uA" },
    { CURRENTPOSITION_25uA,     "25uA" },
    { CURRENTPOSITION_2P5uA,    "2.5uA" },
    { CURRENTPOSITION_250nA,    "250nA" }
};

const QMap<CurrPos_TypeDef, double> Map_CurrValue = {
    { CURRENTPOSITION_auto,     0 },
    { CURRENTPOSITION_100mA,    0.1 },
    { CURRENTPOSITION_25mA,     0.025 },
    { CURRENTPOSITION_2P5mA,    0.0025 },
    { CURRENTPOSITION_250uA,    0.00025 },
    { CURRENTPOSITION_25uA,     0.000025 },
    { CURRENTPOSITION_2P5uA,    0.0000025 },
    { CURRENTPOSITION_250nA,    0.00000025 }
};

const QMap<VolRange_TypeDef, QString> Map_VolRange = {
    { VOLTAGERANGE_auto,        "自动" },
    { VOLTAGERANGE_300mV,       "300mV" },
    { VOLTAGERANGE_30mV,        "30mV" },
    { VOLTAGERANGE_3mV,         "3mV" },
};

const QMap<MeasureMode_TypeDef, QString> Map_MeasureMode = {
    { MODE_SINGLE,                      "单次测量" },
    { MODE_10TIMES_SINGLEPOINT_AUTO,    "自动单点10次测量" },
    { MODE_10TIMES_SINGLEPOINT_MAN,     "手动单点10次测量" },
    { MODE_10TIMES_MULTIPOINT_MAN,      "手动多点10次测量" }
};

const QMap<ParamName_TypeDef, QString> Map_ParamName = {
    { NAME_SemiType,            "SemiType:" },
    { NAME_Temperature,         "Temperature:" },
    { NAME_SampleThickness,     "SampleThickness:" },
    { NAME_SampleDiameter,      "SampleDiameter:" },
    { NAME_ProbeSpacing,        "ProbeSpacing:" },
    { NAME_FspCorrectionFactor, "FspCorrectionFactor:" },
    { NAME_a,                   "a:" },
    { NAME_b,                   "b:" },
    { NAME_CurrErrorBound,      "CurrentErrorBound:" },
    { NAME_ControlVoltages,     "ControlVoltages:" },
    { NAME_CurrPos,             "CurrentPosition:" },
    { NAME_VolRange,            "VoltageRange:" },
    { NAME_MeasureMode,         "MeasureMode:" },
    { NAME_PID_Kp,              "PID_Kp:" },
    { NAME_PID_Ti,              "PID_Ti:" },
    { NAME_PID_Td,              "PID_Td:" },
    { NAME_PIDControlEnabled,   "PIDControlEnabled:" }
};

const QMap<ValueType_TypeDef, QString> Map_ValueType = {
    { VALUE_CURRENT,            "Current" },
    { VALUE_VOLTAGE,            "Voltage" },
    { VALUE_RESISTANCE,         "Resistance" },
    { VALUE_RESISTIVITY,        "Resistivity" },
    { VALUE_SP_Current,         "SP_Current" },
    { VALUE_Last_uk,            "Last_uk" },
    { VALUE_delta_uk,           "delta_uk" },
    { VALUE_Err,                "Err" },
    { VALUE_uk,                 "uk" }
};
