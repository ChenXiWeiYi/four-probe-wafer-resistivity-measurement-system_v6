#include "main.h"

/** @date 2026.01.13 */ 

int main(void)
{
	int cnt_Measure = 0;
	int cnt = 0;
	TIMPara_InitDef TIMPara_Init;

	
	__disable_irq();	// 禁用全局中断
	
		
	HAL_Init();						// 初始化HAL库    
	Stm32_Clock_Init(336,8,2,7);	// 设置时钟,168Mhz
	
	delay_init(168);				// 初始化延时函数

	// NVIC优先级分组
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0); 

		
	GPIO_Init();					// GPIO初始化	
		
	SPI_Init();	// SPI初始化
	CS_ADC1 = 0;
	CS_ADC2 = 0;
	DSYNC_ADC1 = 1;
	DSYNC_ADC2 = 1;

	delay_ms(1000);
	LED2 = 1;
	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC2, PIN_DRDY_ADC2) == GPIO_PIN_SET);	// 等到DRDY拉低再写初始化
	LED4 = 1;

	ADC2_Init();
	LED3 = 1;	
	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC1, PIN_DRDY_ADC1) == GPIO_PIN_SET);	// 等到DRDY拉低再写初始化
	ADC1_Init();
	LED4 = 1;
//	printf("Test:ADC1 Init Finish\r\n");


//	printf("Test:ADC2 Init Finish\r\n");
//	while((HAL_GPIO_ReadPin(GPIO_DRDY_ADC1, PIN_DRDY_ADC1) == GPIO_PIN_SET) || (HAL_GPIO_ReadPin(GPIO_DRDY_ADC2, PIN_DRDY_ADC2) == GPIO_PIN_SET));	// 等到DRDY拉低再配置EXTI
	EXTI_Init();	

	
	USART_Init((uint32_t)115200);		// 初始化USART
	

	TIMPara_Init.TIM2_ARR=50-1;	// 定时器2的ARR为5000-1
	TIMPara_Init.TIM2_PSC=84-1;
//	TIMPara_Init.TIM3_ARR=84-1;	// 定时器3的ARR为5000-1
//	TIMPara_Init.TIM3_PSC=50-1;
	TIM_Init(TIMPara_Init);			// 定时器初始化，定时器时钟为84M

	__enable_irq();	// 使能全局中断
	
	CCS_GND = 1;

	OE_595=0;
	MR_595=1;
	CLR_CurrentPosition();


	
	delay_ms(1000);
	
	DSYNC_ADC2 = 0;
	DSYNC_ADC1 = 0;
	delay_us(1000);
	DSYNC_ADC2 = 1;
	DSYNC_ADC1 = 1;	

	Set_VoltMeter2_Range(VoltMeter2_RANGE_2P5V);

//	printf("Test:Init Finish\r\n");


	DAC_Write(1.2);
	
	Set_VoltMeter1_Range(VoltMeter1_RANGE_300mV);

	SHCP_595 = 1;

		LED1=1;

	LED4=1;
	LED1=0;
	while(1){
		if(is_USART1_RxOK()){	// 处理USART1
			Process_USART1();
		}
	
		
		// 判断是否测量
		// 判断是否测量
		if(is_Measure()){	// 开始测量
			if(cnt_Measure < 100){
				if(is_Flag_ADC1_DRDY()){
					if(is_Flag_ADC2_DRDY()){
						ADC1_Read();
						CLR_Flag_ADC1_DRDY();
						ADC2_Read();
						CurrentControl_UpdateFromADC();
						CLR_Flag_ADC2_DRDY();
						cnt_Measure = cnt_Measure + 1;
						cnt = cnt + 1;
						Answer_VoltageCurrentUpdate();
					}
				}				
			}else{
				Stop_Measure();		// 停止测量
				cnt_Measure = 0;	// 计数清零
				
				Answer_MeasureComplete();
				LED4 = !LED4;
			}
			if(cnt == 200){
				cnt = 0;
				LED1 = !LED1;
			}
		}
		
		if(is_ReadCurrentOnly()){
			if(is_Flag_ADC2_DRDY()){
				if(1){ //(DRDY_ADC2 == 0){
					ADC2_Read();
					CurrentControl_UpdateFromADC();
					CLR_Flag_ADC2_DRDY();
					Answer_ReadCurrentOnly();
					Stop_ReadCurrentOnly();
				}else{
					CLR_Flag_ADC2_DRDY();
				}
			}
		}
		
	}
}




#if 0	// 先测试,不用这部分(2026.02.05)
		// 判断是否测量
		if(is_Measure()){	// 开始测量
			if(cnt_Measure < 1000){
				if(is_Flag_ADC1_DRDY()){
					if(is_Flag_ADC2_DRDY()){
						ADC1_Read();
						CLR_Flag_ADC1_DRDY();
						ADC2_Read();
						CurrentControl_UpdateFromADC();
						CLR_Flag_ADC2_DRDY();
						cnt_Measure = cnt_Measure + 1;
						cnt = cnt + 1;
						Answer_VoltageCurrentUpdate();
					}
				}				
			}else{
				Stop_Measure();		// 停止测量
				cnt_Measure = 0;	// 计数清零
				
				Answer_MeasureComplete();
				LED4 = !LED4;
			}
			if(cnt == 200){
				cnt = 0;
				LED1 = !LED1;
			}
		}
#endif
