#include "widget.h"
#include <QDebug>

/**
 * @brief Widget::DataProcess_ADC1_Voltage 处理ADC1电压数据 (3字节)
 * @param rawData_3Byte 3字节的原始数据
 * @return 计算出的电压值(double)
 * @author 刘嘉诚
 * @date 2026.06.08
 */
double Widget::DataProcess_ADC1_Voltage(const QByteArray &rawData_3Byte)
{
    if (rawData_3Byte.size() != 3) {
        // 错误处理，或者返回 0
        return 0.0;
    }

    // 1. 解析 3字节 -> uint32
    unsigned char byte1 = static_cast<unsigned char>(rawData_3Byte[0]); // 高8b
    unsigned char byte2 = static_cast<unsigned char>(rawData_3Byte[1]); // 中8b
    unsigned char byte3 = static_cast<unsigned char>(rawData_3Byte[2]); // 低8b
    uint32_t ADCValue_u32 = (static_cast<uint32_t>(byte1) << 16)
                          | (static_cast<uint32_t>(byte2) << 8)
                          | static_cast<uint32_t>(byte3);

    // 2. 物理量转换 (具体参数根据你之前的代码保持一致)
    const uint32_t Min_ADCValue = 0x00000;
    const uint32_t Max_ADCValue = 0x7FFFFF;
    const uint32_t Range_ADCValue = Max_ADCValue - Min_ADCValue;
    const double FullScale_Voltage = 5.0;

    double Voltage_d = (static_cast<double>(ADCValue_u32 - Min_ADCValue) / static_cast<double>(Range_ADCValue)) * FullScale_Voltage;

    // 3. 应用增益
    double VolGain = Return_DataGain(VALUE_VOLTAGE);
    Voltage_d = Voltage_d / VolGain;

    return Voltage_d;
}

/**
 * @brief Widget::DataProcess_ADC2_Current 处理ADC2电流数据 (3字节)
 * @param rawData_3Byte 3字节的原始数据
 * @return 计算出的电流值 (double)
 * @author 刘嘉诚
 * @date 2026.06.08
 */
double Widget::DataProcess_ADC2_Current(const QByteArray &rawData_3Byte)
{
    if (rawData_3Byte.size() != 3) {
        return 0.0;
    }

    // 1. 解析 3字节 -> uint32
    unsigned char byte1 = static_cast<unsigned char>(rawData_3Byte[0]);
    unsigned char byte2 = static_cast<unsigned char>(rawData_3Byte[1]);
    unsigned char byte3 = static_cast<unsigned char>(rawData_3Byte[2]);

    qDebug() << "rawData_3Byte hex:" << rawData_3Byte.toHex();

    uint32_t ADCValue_u32 = (static_cast<uint32_t>(byte1) << 16)
                          | (static_cast<uint32_t>(byte2) << 8)
                          | static_cast<uint32_t>(byte3);

    // 2. 物理量转换
    const uint32_t Min_ADCValue = 0x00000;
    const uint32_t Max_ADCValue = 0x7FFFFF;
    const uint32_t Range_ADCValue = Max_ADCValue - Min_ADCValue;
    const double FullScale_Current = 5.0;

    double Current_d = (static_cast<double>(ADCValue_u32 - Min_ADCValue) / static_cast<double>(Range_ADCValue)) * FullScale_Current;

    // 3. 应用增益
    double CurrGain = Return_DataGain(VALUE_CURRENT);
    Current_d = Current_d / CurrGain;

    return Current_d;
}
