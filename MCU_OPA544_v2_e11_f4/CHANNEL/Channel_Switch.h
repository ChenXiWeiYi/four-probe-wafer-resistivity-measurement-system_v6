#ifndef ChannelState_StateTypeDef_H
#define ChannelState_StateTypeDef_H

#include <stdbool.h>
#include "GPIO_Init.h"

typedef enum
{
	Start,
	Shift,
	Storage
}ChannelState_StateTypeDef;

// 恒流源档位
#define Current_POSITION_NONE	0
#define Current_POSITION_100mA	1
#define Current_POSITION_25mA	2
#define Current_POSITION_2P5mA	3
#define Current_POSITION_250uA	4
#define Current_POSITION_25uA	5
#define Current_POSITION_2P5uA	6
#define Current_POSITION_250nA	7

// 电压测量档位
#define VoltMeter1_RANGE_NONE	0
#define VoltMeter1_RANGE_300mV	1
#define VoltMeter1_RANGE_30mV	2
#define VoltMeter1_RANGE_3mV	3

// 电流测量档位
#define VoltMeter2_RANGE_NONE	0
#define VoltMeter2_RANGE_2P5V	1
#define VoltMeter2_RANGE_250mV	2

// LTC6373增益
#define LTC6373_off			0
#define LTC6373_GAIN025		1
#define LTC6373_GAIN05		2
#define LTC6373_GAIN1		3
#define LTC6373_GAIN2		4
#define LTC6373_GAIN4		5
#define LTC6373_GAIN8		6
#define LTC6373_GAIN16		7

#define Proportion_UpperBound	1
#define Proportion_LowerBound	0.09

// 恒流源压控输入
#define SP_Voltage_NONE		0
#define SP_Voltage_100mA	2.5
#define SP_Voltage_25mA		2.5
#define SP_Voltage_2P5mA	2.5
#define SP_Voltage_250uA	2.521
#define SP_Voltage_25uA		2.5
#define SP_Voltage_2P5uA	2.5
#define SP_Voltage_250nA	0.25



/**  Set_Current_Position.c  **/
void Set_Current_Position(int CurrPos);	// 设置通道并启动通道切换
void Channel_Switch(void);	// // 在TIM2的中断服务-回调函数中被调用
void CLR_CurrentPosition(void);
bool is_CurrPosSwitch(void);
void Set_CurrentPositionDoneNotify(uint8_t seq, uint8_t originCtrlByte);
void Process_CurrentPositionDoneNotify(void);

/**  Set_VoltMeter1_Range.c  **/
void Set_VoltMeter1_Range(int Range_Vol1);
void Set_ADC1Driver_Gain1(void);

/**  Auto_Select_Channel.c  **/
bool Start_AutoSelChannel(void);
void Enable_AutoSelChannel(void);
void Disable_AutoSelChannel(void);

/**  Set_VoltMeter2_Range.c  **/
void Set_VoltMeter2_Range(int Range_Vol2);

#endif
