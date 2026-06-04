#include "Function_ADC.h"
#if 0
static void	ADC1_Init(void);
static void	ADC2_Init(void);
#endif
static int	delay_time = 1;	// 最小5.5*0.1 us


/** @date 2025.09.01 */
void ADC_Init(void)
{
	ADC1_Init();
	ADC2_Init();
}


/** @date 2025.11.09 */
void ADC1_Init(void)
{
// 初始化
#if 1
	uint8_t CMR3_Init[2] = {0x04,0x02};	// 0000 0010,不使用偏置电压,不使用参考电压,800000H~7FFFFFH,单极,M2L,MSB,SDOUT(2025.09.05
	uint8_t CMR2_Init[2] = {0x05,0x00}; // 0000 0000,正常工作,增益为1,通道为1
	uint8_t CMR1_Init[2] = {0x06,0x40};	// 0110 0000,Turbo速率4,采样比194
	uint8_t CMR0_Init[2] = {0x07,0xC2};	// 1100 0010,采样比194
#endif
	uint8_t CMR_Init[5] = {0x64,0x02,0x00,0x40,0xC2};
// 校正
	uint8_t Cali_Init[2] = {0x05,0x00};

	CS_ADC1 = 0;
	delay_us(5);

#if 1
	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC1, PIN_DRDY_ADC1) == GPIO_PIN_SET);	// µÈµ½DRDYÀ­µÍÔÙÐ´³õÊ¼»¯
	HAL_SPI_Transmit(&SPI1_Handler, CMR_Init, 5, 100);
	delay_us(1);
	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC1, PIN_DRDY_ADC1) == GPIO_PIN_RESET);	// 等到DRDY拉低再让校正
#endif

#if 0	// 四个CMR分别初始化
	HAL_SPI_Transmit(&SPI1_Handler,CMR3_Init,2,100);
	delay_us(delay_time); 
	HAL_SPI_Transmit(&SPI1_Handler,CMR2_Init,2,100);
	delay_us(delay_time);
	HAL_SPI_Transmit(&SPI1_Handler,CMR1_Init,2,100);
	delay_us(delay_time);
	HAL_SPI_Transmit(&SPI1_Handler,CMR0_Init,2,100);
	delay_us(delay_time);
#endif



#if 1
	Cali_Init[1] = 0x20;	// 自校正
	HAL_SPI_Transmit(&SPI1_Handler,Cali_Init,2,100);
	delay_us(delay_time);
	Cali_Init[1] = 0x40;	// 自校正
	HAL_SPI_Transmit(&SPI1_Handler,Cali_Init,2,100);
	delay_us(delay_time);	
	Cali_Init[1] = 0x80;	// 自校正
	HAL_SPI_Transmit(&SPI1_Handler,Cali_Init,2,100);
	delay_us(delay_time);	
#endif
}


/** @date 2025.08.30 */
void ADC2_Init(void)
{
// 初始化
#if 1
	uint8_t CMR3_Init[2] = {0x04,0x02};	// 0000 0010,不使用偏置电压,不使用参考电压,800000H~7FFFFFH,单极,M2L,MSB,SDOUT(2025.09.05
	uint8_t CMR2_Init[2] = {0x05,0x00}; // 0000 0000,正常工作,增益为1,通道为1
	uint8_t CMR1_Init[2] = {0x06,0x40};	// 0110 0000,Turbo速率4,采样比194
	uint8_t CMR0_Init[2] = {0x07,0xC2};	// 1100 0010,采样比194
#endif
	uint8_t CMR_Init[5] = {0x64,0x02,0x00,0x40,0xC2};
// 校正
	uint8_t Cali_Init[2] = {0x05,0x00};

	CS_ADC2 = 0;
	delay_us(5);

#if 1
//	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC2, PIN_DRDY_ADC2) == GPIO_PIN_SET);	// 等到DRDY拉高再写初始化
	HAL_SPI_Transmit(&SPI3_Handler, CMR_Init, 5, 100);
	delay_us(1);
//	while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC2, PIN_DRDY_ADC2) == GPIO_PIN_RESET);	// 等到DRDY拉低再让校正
#endif
//while(HAL_GPIO_ReadPin(GPIO_DRDY_ADC2, PIN_DRDY_ADC2) == GPIO_PIN_SET);	// µÈµ½DRDYÀ­µÍÔÙÐ´³õÊ¼»¯
#if 0	// 四个CMR分别初始化
	HAL_SPI_Transmit(&SPI3_Handler,CMR3_Init,2,100);
	delay_us(delay_time); 
	HAL_SPI_Transmit(&SPI3_Handler,CMR2_Init,2,100);
	delay_us(delay_time);
	HAL_SPI_Transmit(&SPI3_Handler,CMR1_Init,2,100);
	delay_us(delay_time);
	HAL_SPI_Transmit(&SPI3_Handler,CMR0_Init,2,100);
	delay_us(delay_time);
#endif



#if 1
	Cali_Init[1] = 0x20;	// 自校正
	HAL_SPI_Transmit(&SPI3_Handler,Cali_Init,2,100);
	delay_us(delay_time);
	Cali_Init[1] = 0x40;	// 自校正
	HAL_SPI_Transmit(&SPI3_Handler,Cali_Init,2,100);
	delay_us(delay_time);	
	Cali_Init[1] = 0x80;	// 自校正
	HAL_SPI_Transmit(&SPI3_Handler,Cali_Init,2,100);
	delay_us(delay_time);	
#endif
}



void Test_ADC1_REFO(void)
{
	static bool flag = false;
	uint8_t CMR3_Init[2] = {0x04,0x02};	// 0000 0010,不使用偏置电压,不使用参考电压,800000H~7FFFFFH,单极,M2L,MSB,SDOUT(2025.09.05
	
	if(flag)
	{
		CMR3_Init[1] = 0x02;
		HAL_SPI_Transmit(&SPI1_Handler,CMR3_Init,2,100);
	}else
	{
		CMR3_Init[1] = 0x42;
		HAL_SPI_Transmit(&SPI1_Handler,CMR3_Init,2,100);
	}
	flag = !flag;
}
