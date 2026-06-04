#include "EXTI_Init.h"

/** 
 * @brief 设置中断优先级，使能外部中断
 * @date 2026.01.12
 */

void EXTI_Init(void)
{
// 核心板按键
// EXTI2	PE2,管脚映射在"KeyBoardKey_GPIO_Init.c",KEY4
	HAL_NVIC_SetPriority(EXTI2_IRQn,3,3);		// 抢占优先级3,响应优先级3
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
// EXTI6	PC6,管脚映射在"KeyBoardKey_GPIO_Init.c",KEY1
	HAL_NVIC_SetPriority(EXTI9_5_IRQn,3,0);		// 抢占优先级3,响应优先级0
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
// EXTI13	PC13,管脚映射在"KeyBoardKey_GPIO_Init.c",KEY2
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,3,1);	// 抢占优先级3,响应优先级1
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
// EXTI14	PD14,管脚映射在"KeyBoardKey_GPIO_Init.c",KEY3

// ADC
// EXTI1	PB1,管脚映射在"ADC_GPIO_Init.c",ADC1_DRDY
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
	HAL_NVIC_SetPriority(EXTI1_IRQn,0,2);		// 抢占优先级0,响应优先级1
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
// EXTI4	PD4,管脚映射在"ADC_GPIO_Init.c",ADC2_DRDY
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
	HAL_NVIC_SetPriority(EXTI4_IRQn,0,1);		// 抢占优先级0,响应优先级0
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}


/** @brief 调用中断处理公用函数,包含中断标志清零和调用回调函数 */
void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6); };
}
void EXTI15_10_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13); };
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14); };
}


/** @brief 回调函数
 *
 * 从中断处理公用函数最后会调用
 *
 * @param GPIO_Pin 触发外部中断的管脚
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:
//			KEY_UP_Interrupt();
			break;
		case GPIO_PIN_1:
			EXTI1_Interrupt();
			break;
		case GPIO_PIN_2:
			EXTI2_Interrupt();
			break;
		case GPIO_PIN_3:
//			Key_o2G_Interrupt();
			break;
		case GPIO_PIN_4:
			EXTI4_Interrupt();
			break;
		case GPIO_PIN_6:
			EXTI6_Interrupt();
			break;
		case GPIO_PIN_13:
			EXTI13_Interrupt();
			break;
		case GPIO_PIN_14:
			EXTI14_Interrupt();
			break;
	}

}
