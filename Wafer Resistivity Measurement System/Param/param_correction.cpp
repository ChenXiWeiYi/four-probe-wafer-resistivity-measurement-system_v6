#include "widget.h"

/**
 * @brief Widget::Update_GeometryCorrectionFactor 更新几何修正因子
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Update_GeometryCorrectionFactor(void)
{
    // 厚度修正
    Param_used.ThicknessCorrectionFactor = LinearInterpolate(Map_ThicknessCorrectionFactor, Param_used.WS);
    // 直径修正
    if(Param_used.WS >= 2.5){
        Param_used.F2CorrectionFactor = 4.532;
    }else{
        Param_used.F2CorrectionFactor = LinearInterpolate(Map_F2CorrectionFactor, Param_used.SD);
    }
    // 几何修正
    Param_used.GeometryCorrectionFactor = Param_used.ThicknessCorrectionFactor * Param_used.SampleThickness
            * Param_used.F2CorrectionFactor * Param_used.FspCorrectionFactor / 10;  // 厚度从mm转cm
}

/**
 * @brief Widget::Update_CorrectionFactor 更新修正因子
 * 温度修正因子与电阻率相关,需要输入电阻
 * @param Resistance 直接电压比电流的电阻
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Update_CorrectionFactor(double Resistance)
{
    double ResitivityTemperatureCoefficient;
    double Resitivity_T = Resistance * Param_used.GeometryCorrectionFactor;

    if (Param_used.SemiType == SEMITYPE_P) {
        ResitivityTemperatureCoefficient = LinearInterpolate(Map_TemperatureCoefficient_23_p, Resitivity_T);
    } else {
        ResitivityTemperatureCoefficient = LinearInterpolate(Map_TemperatureCoefficient_23_n, Resitivity_T);
    }

    Param_used.TemperatureCorrectionFactor = 1.0 - ResitivityTemperatureCoefficient * (Param_used.Temperature - 23.0);
    Param_used.CorrectionFactor = Param_used.GeometryCorrectionFactor * Param_used.TemperatureCorrectionFactor;
}

/**
 * @brief 通用线性内插工具函数
 * @param map 查值的表 (Key=输入量, Value=结果量)
 * @param inputX 需要查询的输入值 X
 * @return 内插后的结果值 Y
 * @author 刘嘉诚
 * @date 2026.06.08
 */
double Widget::LinearInterpolate(const QMap<double, double>& map, double inputX)
{
    if (map.isEmpty()) return 0.0;

    if (inputX <= map.firstKey()) return map.first();
    if (inputX >= map.lastKey())  return map.last();

    auto itUpper = map.upperBound(inputX);
    auto itLower = itUpper - 1; // 左边那个点

    // 4. 提取四个坐标点 (x1, y1) 和 (x2, y2)
    double x1 = itLower.key();
    double y1 = itLower.value();
    double x2 = itUpper.key();
    double y2 = itUpper.value();

    // 5. 线性内插公式 (点斜式)
    // y = y1 + (y2 - y1) * (x - x1) / (x2 - x1)
    // 加上分母防零保护 (虽然在Map里key是唯一的，一般不会x2==x1)
    if (qFuzzyCompare(x1, x2)) return y1;

    double resultY = y1 + (y2 - y1) * (inputX - x1) / (x2 - x1);
    return resultY;
}
