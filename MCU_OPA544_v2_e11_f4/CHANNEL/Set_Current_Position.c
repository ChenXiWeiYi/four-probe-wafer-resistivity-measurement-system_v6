#include "Channel_Switch.h"
#include "TIM_Init.h"
#include "Function_DAC.h"
#include "Function_ADC.h"
#include "Answer_Handler.h"



static void Enable_CurrentPosition_Switch(void);
static void Channel_Switch_ok(void);

static int num_595 = 0;

volatile uint8_t	CurrPos_Sel = Current_POSITION_NONE;

static bool	Flag_CurrPos2None = true;		// Flag_CurrPos2None 是否输出空通道，初始状态输出空通道
static volatile bool	Flag_CurrPosSwitch = false;		// 是否启动通道切换，初始状态不启动切换
static volatile bool Flag_CurrPosDonePending = false;
static volatile bool Flag_CurrPosDoneReady = false;
static volatile uint8_t CurrPosDoneSeq = 0;
static volatile uint8_t CurrPosDoneCtrlByte = 0;

ChannelState_StateTypeDef CommState_595 = Start;	// 595通讯状态,Shift：595移入DS上的状态,Storage：595更新输出

static float SP_Voltage[8] = {	SP_Voltage_NONE,SP_Voltage_100mA,SP_Voltage_25mA,SP_Voltage_2P5mA,
								SP_Voltage_250uA,SP_Voltage_25uA,SP_Voltage_2P5uA,SP_Voltage_250nA};

/**
 * @brief	按位输出到595
 *
 * 在TIM2的中断回调函数中被调用
 *
 * @author	刘嘉诚
 * @date	2025.08.31
 */
void Channel_Switch(void)
{
	uint8_t	CurrPos_Out = Current_POSITION_NONE;
	// 切换通道
	if(Flag_CurrPosSwitch){
		if(Flag_CurrPos2None){
			CurrPos_Out = Current_POSITION_NONE;	// 判断输出空通道或选择的通道
		}else{
			CurrPos_Out = CurrPos_Sel;
		}
		if(num_595 <= 7){
			switch(CommState_595){
				case(Start):
					SHCP_595 = 0;
					STCP_595 = 0;
					DS_595 = (CurrPos_Out >> num_595) & 0x01;
					num_595++;
					CommState_595 = Shift;
					break;
				case(Shift):
					SHCP_595 = 1;
					LED3 = !LED3;
//					STCP_595 = 0;
					CommState_595 = Storage;
					break;
				case(Storage):
					SHCP_595 = 0;
//					STCP_595 = 1;
					DS_595 = (CurrPos_Out >> num_595) & 0x01;
					num_595++;
					CommState_595 = Shift;
					break;
			}
		}else if(num_595 == 8){
			SHCP_595 = 1;
//			STCP_595 = 0;
			num_595++;
		}else if(num_595 == 9){
			SHCP_595 = 0;
			STCP_595 = 1;
			num_595++;
		}else{
			num_595 = 0;
			STCP_595 = 0;
			CommState_595 = Start;
			if(!Flag_CurrPos2None) Channel_Switch_ok(); // 如果此时Flag_Channel2None是false，则表明通道切换完成
			Flag_CurrPos2None = !Flag_CurrPos2None;
//			LED5 = !LED5;
		}
	}
}


/**
 * @brief Set_Current_Position 修改使用的通道,启动通道切换
 * @author 刘嘉诚
 * @date 2026.01.30
 */
void Set_Current_Position(int CurrPos)
{

	if(CurrPos >= Current_POSITION_100mA && CurrPos <= Current_POSITION_2P5uA){
		Set_VoltMeter2_Range(VoltMeter2_RANGE_NONE);
		DAC_Write(SP_Voltage[CurrPos]);
		CurrPos_Sel = (1 << CurrPos);
		Enable_CurrentPosition_Switch();
		Set_VoltMeter2_Range(VoltMeter2_RANGE_2P5V);
	}else if(CurrPos == Current_POSITION_250nA){
		Set_VoltMeter2_Range(VoltMeter2_RANGE_NONE);
		DAC_Write(SP_Voltage[CurrPos]);
		CurrPos_Sel = (1 << Current_POSITION_2P5uA);	// 继电器档位和2.5uA一样
		Enable_CurrentPosition_Switch();
		Set_VoltMeter2_Range(VoltMeter2_RANGE_250mV);
	}else{
		Answer_Error(Error_UnknownCurrentPosition);
	}
}


/**
 * @brief	通道置空
 *
 * @author	刘嘉诚
 * @date	2025.09.06
 */
void CLR_CurrentPosition(void)
{
	DAC_Write(SP_Voltage[Current_POSITION_NONE]);
	CurrPos_Sel = Current_POSITION_NONE;
	Enable_CurrentPosition_Switch();
}


/** 
 * @author	刘嘉诚
 * @date	2025.09.06
 */
bool is_CurrPosSwitch(void)
{
	return Flag_CurrPosSwitch;
}

/**
 * @brief Set_CurrentPositionDoneNotify
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Set_CurrentPositionDoneNotify(uint8_t seq, uint8_t originCtrlByte)
{
	Flag_CurrPosDonePending = true;
	Flag_CurrPosDoneReady = false;
	CurrPosDoneSeq = seq;
	CurrPosDoneCtrlByte = originCtrlByte;
}

/**
 * @brief Process_CurrentPositionDoneNotify
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Process_CurrentPositionDoneNotify(void)
{
	if(Flag_CurrPosDoneReady){
		uint8_t seq = CurrPosDoneSeq;
		uint8_t originCtrlByte = CurrPosDoneCtrlByte;

		Flag_CurrPosDoneReady = false;
		Flag_CurrPosDonePending = false;
		Answer_OperationDone(seq, originCtrlByte, Error_None);
	}
}


/**
 * @brief	启动通道切换
 *
 * @author	刘嘉诚
 * @date	2025.08.31
 */
static void Enable_CurrentPosition_Switch(void)
{
	if(!Flag_CurrPosSwitch){	// 判断此时是否正在切换通道
		Flag_CurrPosSwitch = true;
		__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);	// 清空TIM2计数
		HAL_TIM_Base_Start_IT(&TIM2_Handler);	// 使能TIM2计数和更新中断
	}
}


/**
 * @brief	通道切换完成
 *
 * @author	刘嘉诚
 * @date	2025.08.31
 */
static void Channel_Switch_ok(void)
{
	Flag_CurrPosSwitch = false;
	HAL_TIM_Base_Stop_IT(&TIM2_Handler);	// 失效TIM2计数和更新中断
	__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);	// 清空TIM2计数
	CurrPos_Sel = Current_POSITION_NONE;
	num_595 = 0;	// 保险,防止多中断一次
	if(Flag_CurrPosDonePending){
		Flag_CurrPosDoneReady = true;
	}
}
