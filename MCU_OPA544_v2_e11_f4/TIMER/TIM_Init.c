#include "TIM_Init.h"
#include "Channel_Switch.h"

void TIM_Init(TIMPara_InitDef TIMPara_Init)
{
	TIM2_Init(TIMPara_Init.TIM2_ARR,TIMPara_Init.TIM2_PSC);
}

/**
 * @brief 时钟配置
 *
 * 在HAL_TIM_Base_Init中调用
 * TIM时钟使能，设置TIM中断优先级，允许TIM中断(未允许具体类型的中断)
 *
 * @param htim 待配置的TIM
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();			// TIM2时钟输出使能(必须有)
		HAL_NVIC_SetPriority(TIM2_IRQn,1,2);	// 抢占优先级1，响应优先级3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);			// 允许TIM2的中断(未允许特定中断)
	}

}

/**
 * @brief TIM回调函数
 *
 * 固定在Update中断后被HAL_TIM_IRQHandler调用
 * 根据中断的TIM调用函数
 *
 * @param htim 中断的TIM
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){ Channel_Switch();}	// 通道切换
}

/**
 * @brief TIM中断服务入口函数
 *
 * 所有的TIM中断服务入口函数，仅用于调用中断服务函数
 *
 */
void TIM2_IRQHandler(void){	HAL_TIM_IRQHandler(&TIM2_Handler);}	// TIM2
