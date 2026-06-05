#ifndef Function_ADC_H
#define Function_ADC_H

#include <stdbool.h>
#include <string.h>
#include "GPIO_Define.h"
#include "sys.h"
#include "SPI_Init.h"
#include "delay.h"

#define SIZE_Data_ADC	3

#define ADC_GAIN1	1
#define ADC_GAIN2	2
#define ADC_GAIN4	3
#define ADC_GAIN8	4
#define ADC_GAIN16	5

extern uint8_t Data_ADC1_u8[SIZE_Data_ADC];
extern uint8_t Data_ADC2_u8[SIZE_Data_ADC];

/** Function_ADC_Init.c */
void ADC_Init(void);
void ADC1_Init(void);
void ADC2_Init(void);
void Test_ADC1_REFO(void);

/** Function_ADC_Read.c */
void	ADC1_Read(void);
void	ADC2_Read(void);
bool	is_ADC1_ReadComplete(void);
bool	is_ADC2_ReadComplete(void);
float	Return_Data_ADC1_f(void);
float	Return_Data_ADC2_f(void);

/** Function_ADC_Gain.c */
void Set_ADC1_Gain(int num_Gain);
void Set_ADC2_Gain(int num_Gain);

#endif
