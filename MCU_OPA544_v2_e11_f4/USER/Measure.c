#include "Measure.h"

static bool Flag_Measure = false;
static bool Flag_ReadCurrentOnly = false;

/**
 * @brief Start_Measure 开始测量
 * @author 刘嘉诚
 * @date 2025.10.24
 */
void Start_Measure(void)
{
	Flag_Measure = true;
	Flag_ReadCurrentOnly = false;
	CS_ADC1 = 0;
	CS_ADC2 = 0;
	delay_ms(1);
	DSYNC_ADC1 = 0;
	DSYNC_ADC2 = 0;
	delay_ms(1);
	DSYNC_ADC1 = 1;
	DSYNC_ADC2 = 1;
}


/**
 * @brief Stop_Measure 停止测量
 * @author 刘嘉诚
 * @date 2025.10.24
 */
void Stop_Measure(void)
{
	Flag_Measure = false;
	CS_ADC1 = 1;
	CS_ADC2 = 1;	
}


/**
 * @brief is_Measure 是否开始测量
 * @return 是否开始测量
 * @author 刘嘉诚
 * @date 2025.10.24
 */
bool is_Measure(void)
{
	return Flag_Measure;
}

/**
 * @brief Start_ReadCurrentOnly
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Start_ReadCurrentOnly(void)
{
	if(is_Measure()){
		return;
	}else{
		Flag_ReadCurrentOnly = true;
		CS_ADC2 = 0;
		delay_ms(1);
	}
}

/**
 * @brief Stop_ReadCurrentOnly
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Stop_ReadCurrentOnly(void)
{
	Flag_ReadCurrentOnly = false;
	CS_ADC2 = 1;
}

/**
 * @brief is_ReadCurrentOnly
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool is_ReadCurrentOnly(void)
{
	return Flag_ReadCurrentOnly;
}
