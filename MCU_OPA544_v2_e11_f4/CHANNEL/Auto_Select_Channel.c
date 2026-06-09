#include "Channel_Switch.h"
#include "Measure.h"
#include "Answer_Handler.h"
#include "Function_ADC.h"
#include "EXTI_Init.h"

static bool is_SuitMeasPos(int VoltRange,int CurrentPos);
static void Read_FreshMeasureSample(void);

static bool Flag_ChannelSwitchAuto = true;


/**
 * @brief	自动切换档位
 *
 * @return	是否找到档位
 * @author	刘嘉诚
 * @date	2026.02.03
 */
bool Start_AutoSelChannel(void)
{
	int		CurrentPos = Current_POSITION_2P5uA;	// 6
	int		VoltRange = VoltMeter1_RANGE_300mV;		// 1
	bool	Flag_ok = false;
	
	if(Flag_ChannelSwitchAuto == true)
	{
		printf("\r\n Auto Select Channel Begin.\r\n");
		CLR_CurrentPosition();
		Set_VoltMeter1_Range(VoltMeter1_RANGE_NONE);

		// 改电流档位
		if((CurrentPos >= Current_POSITION_100mA) && !Flag_ok)
		{
			while(is_CurrPosSwitch() == true);	// 等上一次切换完成
			Set_Current_Position(CurrentPos);	// 设置电流
			while(is_CurrPosSwitch() == true);
			// 改电压档位
			if((VoltRange <= VoltMeter1_RANGE_3mV) && !Flag_ok)
			{
				Set_VoltMeter1_Range(VoltRange);
				Read_FreshMeasureSample();
//				is_Measure_ok();
				Flag_ok = is_SuitMeasPos(VoltRange,CurrentPos);
				Answer_ChannelSwitchProgress(CurrentPos,VoltRange,Flag_ok);	// 发送当前切换状态
				VoltRange++;				
			}
			CurrentPos--;
		}
		// 没有合适的档位
		if(!Flag_ok)
		{
			Answer_Error(Error_NoSuitMeasPos);// 报错
		}
	}
	
	return Flag_ok;
}


/**
 * @brief	判断当前的电流档位和电压量程是否满足要求
 *
 * @param	VoltRange:当前电压档位; CurrentPos:当前电流档位
 * @return	是否当前档位满足要求
 * @author	刘嘉诚
 * @date	2026.02.04
 */
static bool is_SuitMeasPos(int VoltRange,int CurrentPos)
{
	float	Data_ADC1_f = 0;
	float	Data_UpperBound = 0;
	float	Data_LowerBound = 0;
	bool	Flag_ok = false;

	Data_ADC1_f = Return_Data_ADC1_f();
	
	switch(VoltRange)
	{
		case(VoltMeter1_RANGE_300mV):	// 增益8,2.4V
			Data_UpperBound = 2.4*Proportion_UpperBound;
			Data_LowerBound = 2.4*Proportion_LowerBound;
			break;
		case(VoltMeter1_RANGE_30mV):	// 增益128,3.84V
			Data_UpperBound = 3.84*Proportion_UpperBound;
			Data_LowerBound = 3.84*Proportion_LowerBound;
			break;
		case(VoltMeter1_RANGE_3mV):		// 增益256,0.768V
			Data_UpperBound = 0.768*Proportion_UpperBound;
			Data_LowerBound = 0.768*Proportion_LowerBound;
			break;
//		default:
			// 报错
	}

	if(Data_ADC1_f <= Data_UpperBound)	// 小于上边界
	{
		if(Data_ADC1_f >= Data_LowerBound)	// 大于下边界
		{
			Flag_ok = true;
		}
		else if((VoltRange == VoltMeter1_RANGE_3mV) && (CurrentPos == Current_POSITION_100mA))	// 电压最小,电流最大,还是小
		{
			Flag_ok = false;
			Answer_Error(Error_UnderRange);
		}
		else
		{
			Flag_ok = false;
		}
	}
	else if((VoltRange == VoltMeter1_RANGE_300mV) && (CurrentPos == Current_POSITION_250nA))	// 电压最大,电流最小,还是大
	{
		Flag_ok = false;
		Answer_Error(Error_UpRange);
	}
	else	// 其实没有else,写上也行
	{
		Flag_ok = false;
	}
	
	return Flag_ok;
}


/**
 * @brief Read_FreshMeasureSample
 * @author 刘嘉诚
 * @date 2026.06.08
 */
static void Read_FreshMeasureSample(void)
{
	CLR_Flag_ADC1_DRDY();
	CLR_Flag_ADC2_DRDY();
	Start_Measure();

	while(!is_Flag_ADC1_DRDY());
	while(!is_Flag_ADC2_DRDY());

	ADC1_Read();
	CLR_Flag_ADC1_DRDY();
	ADC2_Read();
	CLR_Flag_ADC2_DRDY();

	Stop_Measure();
}


/**
 * @brief Enable_AutoSelChannel
 * @author 刘嘉诚
 * @date 2025.09.06
 */
void Enable_AutoSelChannel(void)
{
	Flag_ChannelSwitchAuto = true;
}


/**
 * @brief Disable_AutoSelChannel
 * @author 刘嘉诚
 * @date 2025.09.06
 */
void Disable_AutoSelChannel(void)
{
	Flag_ChannelSwitchAuto = false;
}
