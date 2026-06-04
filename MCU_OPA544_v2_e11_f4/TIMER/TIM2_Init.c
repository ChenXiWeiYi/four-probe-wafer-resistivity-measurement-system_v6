#include "TIM_Init.h"

// 595通讯时钟使用TIM2
TIM_HandleTypeDef TIM2_Handler;

void TIM2_Init(u16 ARR,u16 PSC)
{
	TIM2_Handler.Instance			= TIM2;
	TIM2_Handler.Init.Prescaler		= PSC;
	TIM2_Handler.Init.CounterMode	= TIM_COUNTERMODE_UP; 		// 向上计数
	TIM2_Handler.Init.Period		= ARR;
	TIM2_Handler.Init.ClockDivision	= TIM_CLOCKDIVISION_DIV1;	// 时钟不分频
	HAL_TIM_Base_Init(&TIM2_Handler);			// 配置TIM2的时钟、优先级、允许中断

//	HAL_TIM_Base_Start_IT(&TIM2_Handler); //使能定时器2和定时器2更新中断：TIM_IT_UPDATE(2025.08.31 初始状态不使能计数和更新中断)

}
