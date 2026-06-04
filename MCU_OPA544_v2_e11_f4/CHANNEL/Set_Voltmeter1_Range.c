#include "Channel_Switch.h"
#include "Function_ADC.h"

static void Set_ADC1Driver_1_Gain(int num_Gain);
static void Set_ADC1Driver_2_Gain(int num_Gain);

/**
 * @brief	Set_VoltMeter1_Range设置电压表1的量程
 *
 * @param	Range_Vol1:选择的量程
 * @author	刘嘉诚
 * @date	2025.11.09
 */
void Set_VoltMeter1_Range(int Range_Vol1)
{
	if((Range_Vol1 < VoltMeter1_RANGE_NONE) || (Range_Vol1 > VoltMeter1_RANGE_3mV))
	{
		// 报错
	}
	else
	{
		switch(Range_Vol1)	// 为了安全,先把驱动关了,然后改ADC,最后改驱动到对应倍数
		{
			case(VoltMeter1_RANGE_NONE):	// 关断,ADC1增益改成1
				Set_ADC1Driver_1_Gain(LTC6373_off);
				Set_ADC1Driver_2_Gain(LTC6373_off);
				Set_ADC1_Gain(ADC_GAIN1);
				break;
			case(VoltMeter1_RANGE_300mV):	// LTC6373增益8,ADC增益1,2.4V
				Set_ADC1Driver_1_Gain(LTC6373_off);
				Set_ADC1_Gain(ADC_GAIN1);
				Set_ADC1Driver_2_Gain(LTC6373_GAIN1);
				Set_ADC1Driver_1_Gain(LTC6373_GAIN8);
				break;
			case(VoltMeter1_RANGE_30mV):		// LTC6373增益16,ADC增益8,3.84V
				Set_ADC1Driver_1_Gain(LTC6373_off);
//				Set_ADC1_Gain(ADC_GAIN1);
				Set_ADC1Driver_2_Gain(LTC6373_GAIN8);
				Set_ADC1Driver_1_Gain(LTC6373_GAIN16);
				break;
			case(VoltMeter1_RANGE_3mV):		// LTC6373增益16,ADC增益16,0.768V
				Set_ADC1Driver_1_Gain(LTC6373_off);
				Set_ADC1_Gain(ADC_GAIN4);
				Set_ADC1Driver_2_Gain(LTC6373_GAIN16);
				Set_ADC1Driver_1_Gain(LTC6373_GAIN16);
				break;
//			default:
				// 报错
		}
	}
}
	

/**
 * @brief	设置LTC6373_1的增益
 *
 * @author	刘嘉诚
 * @date	2025.10.24
 */
static void Set_ADC1Driver_1_Gain(int num_Gain)
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
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN025):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN05):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN1):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN2):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN4):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN8):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN16):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 1;
				break;
//	default:
				// 报错
		}
	}
}


/**
 * @brief	Set_ADC1Driver_2_Gain 设置LTC6373_3的增益
 *
 * @author	刘嘉诚
 * @date	2025.10.24
 */
static void Set_ADC1Driver_2_Gain(int num_Gain)
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
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN025):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN05):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN1):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN2):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN4):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN8):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN16):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 1;
				break;
//	default:
				// 报错
		}
	}
}


/**
 * @brief Set_ADC1Driver_Gain1 设置ADC1的驱动的总增益为1
 * @date 2025.10.28
 */
void Set_ADC1Driver_Gain1(void)
{
	Set_ADC1Driver_1_Gain(LTC6373_GAIN1);
	Set_ADC1Driver_2_Gain(LTC6373_GAIN1);
}




#if 0	// 2025.10.26用的是反向的
/**
 * @brief	设置LTC6373_1的增益
 *
 * @author	刘嘉诚
 * @date	2025.10.24
 */
static void Set_ADC1Driver_1_Gain(int num_Gain)
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
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN025):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN05):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN1):
				A2_LTC6373_1 = 1;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN2):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN4):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 1;
				A0_LTC6373_1 = 0;
				break;
			case(LTC6373_GAIN8):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 1;
				break;
			case(LTC6373_GAIN16):
				A2_LTC6373_1 = 0;
				A1_LTC6373_1 = 0;
				A0_LTC6373_1 = 0;
				break;
//	default:
				// 报错
		}
	}
}


/**
 * @brief	Set_ADC1Driver_2_Gain 设置LTC6373_3的增益
 *
 * @author	刘嘉诚
 * @date	2025.10.24
 */
static void Set_ADC1Driver_2_Gain(int num_Gain)
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
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN025):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN05):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN1):
				A2_LTC6373_3 = 1;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN2):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN4):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 1;
				A0_LTC6373_3 = 0;
				break;
			case(LTC6373_GAIN8):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 1;
				break;
			case(LTC6373_GAIN16):
				A2_LTC6373_3 = 0;
				A1_LTC6373_3 = 0;
				A0_LTC6373_3 = 0;
				break;
//	default:
				// 报错
		}
	}
}

#endif
