#ifndef Measure_H
#define Measure_H

#include "sys.h"
#include <stdbool.h>
#include "GPIO_Define.h"
#include "delay.h"

/**   Measure.c   **/
void Start_Measure(void);
void Stop_Measure(void);
bool is_Measure(void);
void Start_ReadCurrentOnly(void);
void Stop_ReadCurrentOnly(void);
bool is_ReadCurrentOnly(void);

#endif
