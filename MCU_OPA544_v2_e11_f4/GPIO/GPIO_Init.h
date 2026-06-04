#ifndef GPIO_Init_H
#define GPIO_Init_H

#include "sys.h"
#include "GPIO_Define.h"

void GPIO_Init(void);
void KeyBoardKey_GPIO_Init(void);
void KeyBoardLED_GPIO_Init(void);
void HC595_GPIO_Init(void);
void ADC_GPIO_Init(void);
void DAC_GPIO_Init(void);
void BAN_ALL_CS(void);
void CCS2GND_GPIO_Init(void);
void LTC6373_GPIO_Init(void);
void MeasureDirection_GPIO_Init(void);
#endif
