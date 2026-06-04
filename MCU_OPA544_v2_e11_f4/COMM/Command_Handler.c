#include "Command_Handler.h"
#include "Answer_Handler.h"
#include "Function_DAC.h"
#include "Channel_Switch.h"
#include "Measure.h"
#include <string.h>

bool Flag_Direction = true;

/**
 * @brief Command_CurrPosSwitch 指令:电流档位切换
 * @param CtrlByte 控制字
 * @date 2026.02.03
 */
void Command_CurrPosSwitch(uint8_t CtrlByte)
{
	uint8_t	CurrPos = CtrlByte & 0x0F;	// 读取通道
	Set_Current_Position((int)CurrPos);	// 设置通道并启动切换
}

/**
 * @brief Command_CurrentControlInputModify 指令:恒流源压控输入修改
 * @param p_SP_Current_u8 恒流源压控输入指针
 * @date 2026.02.03
 */
void Command_CurrentControlInputModify(uint8_t *p_SP_Current_u8)
{
	float SP_Current_f = 0;
	memcpy(&SP_Current_f, p_SP_Current_u8, 4);
	DAC_Write(SP_Current_f);
}

/**
 * @brief Command_StartMeasurement 指令:测量开始
 * @param MeasureDirection 测量方向
 * @date 2026.02.18
 */
void Command_StartMeasurement(uint8_t MeasureDirection)
{
	if(MeasureDirection == 0x00){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);
		LED2 = 0;
		Flag_Direction = true;
	}else if(MeasureDirection == 0xFF){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_SET);
		LED2 = 1;
		Flag_Direction = false;
	}else{
		Answer_Error(Error_UnknownMeasureDirection);
	}
	Start_Measure();
}

void Command_ReadCurrentOnly(void)
{
	Start_ReadCurrentOnly();
}

/**
 * @brief Command_VoltRangeSwitch 指令:电压档位切换
 * @param CtrlByte 控制字
 * @date 2026.02.03
 */
void Command_VoltRangeSwitch(uint8_t CtrlByte)
{
	int	VolRange = (int)(CtrlByte & 0x0F);	// 读取通道
	
	if((VolRange < 0) || (VolRange > 3)){	// 其实u8转的int不可能小于0,这里这么写好看
		Answer_Error(Error_VoltageRangeError);
	}else{
		if(VolRange == 0){
			// 自动切换档位,这个功能目前设计放在上位机 2025.11.03
		}else{
			Set_VoltMeter1_Range(VolRange);
		}
	}
}

bool Return_Direction(void)
{
	return Flag_Direction;
}
