#include "Channel_Switch.h"
#include "Function_ADC.h"

static void Set_ADC2Driver_Gain(int num_Gain);

/**
 * @brief	Set_VoltMeter2_Range设置电压表2的量程
 *
 * @param	Range_Vol2:选择的量程
 * @author	刘嘉诚
 * @date	2025.10.29
 */
void Set_VoltMeter2_Range(int Range_Vol2)
{
	if((Range_Vol2 < VoltMeter2_RANGE_NONE) || (Range_Vol2 > VoltMeter2_RANGE_250mV))
	{
		// 报错
	}
	else
	{
		switch(Range_Vol2)	// 为了安全,先把驱动关了,然后改ADC,最后改驱动到对应倍数
		{
			case(VoltMeter2_RANGE_NONE):	// 关断,ADC1增益改成1
				Set_ADC2Driver_Gain(LTC6373_off);
//				Set_ADC2_Gain(ADC_GAIN1);
				break;
			case(VoltMeter2_RANGE_2P5V):	// LTC6373增益1,ADC增益1,2.5V
				Set_ADC2Driver_Gain(LTC6373_off);
//				Set_ADC2_Gain(ADC_GAIN1);
				Set_ADC2Driver_Gain(LTC6373_GAIN1);
				break;
			case(VoltMeter2_RANGE_250mV):		// LTC6373增益8,ADC增益1,2V
				Set_ADC2Driver_Gain(LTC6373_off);
//				Set_ADC2_Gain(ADC_GAIN1);
				Set_ADC2Driver_Gain(LTC6373_GAIN8);
				break;
//			default:
				// 报错
		}
	}
}
	

/**
 * @brief	设置LTC6373_2的增益
 * @author	刘嘉诚
 * @date	2025.10.29
 */
static void Set_ADC2Driver_Gain(int num_Gain)
{
	if((num_Gain < LTC6373_off) || (num_Gain > LTC6373_GAIN16))
	{
		// 报错
	}
	else
	{
		switch(num_Gain)
		{
			case(LTC6373_off):
				A2_LTC6373_2 = 0;
				A1_LTC6373_2 = 0;
				A0_LTC6373_2 = 0;
				break;
			case(LTC6373_GAIN025):
				A2_LTC6373_2 = 0;
				A1_LTC6373_2 = 0;
				A0_LTC6373_2 = 1;
				break;
			case(LTC6373_GAIN05):
				A2_LTC6373_2 = 0;
				A1_LTC6373_2 = 1;
				A0_LTC6373_2 = 0;
				break;
			case(LTC6373_GAIN1):
				A2_LTC6373_2 = 0;
				A1_LTC6373_2 = 1;
				A0_LTC6373_2 = 1;
				break;
			case(LTC6373_GAIN2):
				A2_LTC6373_2 = 1;
				A1_LTC6373_2 = 0;
				A0_LTC6373_2 = 0;
				break;
			case(LTC6373_GAIN4):
				A2_LTC6373_2 = 1;
				A1_LTC6373_2 = 0;
				A0_LTC6373_2 = 1;
				break;
			case(LTC6373_GAIN8):
				A2_LTC6373_2 = 1;
				A1_LTC6373_2 = 1;
				A0_LTC6373_2 = 0;
				break;
			case(LTC6373_GAIN16):
				A2_LTC6373_2 = 1;
				A1_LTC6373_2 = 1;
				A0_LTC6373_2 = 1;
				break;
//	default:
				// 报错
		}
	}
}


