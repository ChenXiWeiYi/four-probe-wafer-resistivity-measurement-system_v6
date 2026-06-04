#include "GPIO_Init.h"
#include "SPI_Init.h"
#include "delay.h"
#include "sys.h"

#ifndef Function_DAC_H
#define Function_DAC_H

#define Data_FS_f	3	// (2025.08.30)DAC满量程3V

#endif

void DAC_Write(float Data_f);
