#ifndef GLOBAL_MAPS_H
#define GLOBAL_MAPS_H

#include <QMap>
#include <QString>
#include "global_struct_define.h"

extern const QMap<ParamName_TypeDef, QString> Map_ParamName;

// 声明：电流档位 -> 显示字符 (用于UI)
extern const QMap<CurrPos_TypeDef, QString> Map_CurrPos;
extern const QMap<CurrPos_TypeDef, double> Map_CurrValue;
extern const QMap<VolRange_TypeDef, QString> Map_VolRange;
extern const QMap<MeasureMode_TypeDef,QString> Map_MeasureMode;

extern const QMap<ValueType_TypeDef,QString> Map_ValueType;

extern const QMap<double, double> Map_F2CorrectionFactor;
extern const QMap<double, double> Map_TemperatureCoefficient_23_p;
extern const QMap<double, double> Map_TemperatureCoefficient_23_n;
extern const QMap<double, double> Map_ThicknessCorrectionFactor;


#endif // GLOBAL_MAPS_H
