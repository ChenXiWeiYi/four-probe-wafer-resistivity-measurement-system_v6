#include "widget.h"



/**
 * @brief Process_Resistivity
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Process_Resistivity(double Voltage, double Current)
{
    double Resistance = Voltage / Current;
    MeasureValueStruct_TypeDef MeasureValueStruct;

    Update_CorrectionFactor(Resistance);

    double Resistivity = Param_used.CorrectionFactor * Resistance;
    Update_RealtimeMeasureDisplay(Voltage, Current, Resistance, Resistivity);

    AppendValueToFile(Voltage, VALUE_VOLTAGE);
    AppendValueToFile(Current, VALUE_CURRENT);
    AppendValueToFile(Resistance, VALUE_RESISTANCE);
    AppendValueToFile(Resistivity, VALUE_RESISTIVITY);

    MeasureValueStruct.Voltage = Voltage;
    MeasureValueStruct.Current = Current;
    MeasureValueStruct.Resistance = Resistance;
    MeasureValueStruct.Resistivity = Resistivity;

    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        Buffer_MeasureValue_f.append(MeasureValueStruct);
    }else{
        Buffer_MeasureValue_r.append(MeasureValueStruct);
    }
    Add_Resistivity2Table(Resistivity);
}
