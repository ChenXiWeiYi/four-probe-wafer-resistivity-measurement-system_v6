#ifndef TIM_Init_H
#define TIM_Init_H

#include "sys.h"

/** @brief 所有TIM的ARR和PSC
 */
typedef struct
{
	u16 TIM2_ARR;
	u16 TIM2_PSC;
	u16	TIM3_ARR;
	u16	TIM3_PSC;
}TIMPara_InitDef;


extern TIMPara_InitDef TIMPara_Init;
extern TIM_HandleTypeDef TIM2_Handler;
extern TIM_HandleTypeDef TIM3_Handler;


void TIM_Init(TIMPara_InitDef TIMPara_Init);
void TIM2_Init(u16 ARR,u16 PSC);
void TIM3_Init(u16 ARR,u16 PSC);

#endif
