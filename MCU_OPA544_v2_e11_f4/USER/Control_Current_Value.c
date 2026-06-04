#include "Control_Current_Value.h"

static float SP_Current = 0;
static float PV_Current = 2.5;
static float Kp = 0;		// 比例系数
static float Ti = 1000000000000;		// 积分时间
static float Td = 0;	// 微分时间
static float dt = 1;		// 时间间隔
static bool flag_AutoModifyCurrnt = false;

static void Modify_Current_Value(void);

/**
 * @brief 是否自动修改电流值
 *
 */
void if_Auto_Modify_Current(bool flag_AutoModifyCurrnt_new)
{
	flag_AutoModifyCurrnt = flag_AutoModifyCurrnt_new;
}

/**
 * @brief 修改电流设定值
 * @param SP_Current_new 新的电流设定值
 */
void Modify_SP_Current(float SP_Current_new)
{
	SP_Current = SP_Current_new;
}

/**
 * @brief 修改电流测量值
 * @param PV_Current_new 新的电流测量值
 */
void Modify_PV_Current(float PV_Current_new)
{
	PV_Current = PV_Current_new;
	if(flag_AutoModifyCurrnt)
	{
		Modify_Current_Value();
	}
}

/**
 * @brief 修改电流输出值
 * 仅在 Modify_PV_Current 中被调用
 */
static void Modify_Current_Value(void)
{
	float Error_Current = 0;
	static float Error_Current_1 = 0;		// 上一个误差
	static float Sigma_Error_Current = 0;	// 总误差
	float OutputValue_Current_f = 2.5;
	uint16_t OutputValue_Current_u16 = 0;
	uint8_t OutputValue_Current_u8[2] = {0};

	Error_Current_1 = Error_Current;
	Error_Current = PV_Current - SP_Current;
	Sigma_Error_Current = Sigma_Error_Current + Error_Current;
	OutputValue_Current_f = Kp * Error_Current + Sigma_Error_Current / Ti * dt + Td * (Error_Current - Error_Current_1) / dt;
	
	OutputValue_Current_u16 = (uint16_t)(OutputValue_Current_f/5*65535);
	OutputValue_Current_u8[0] = (OutputValue_Current_u16>>8) & 0xFF;
	OutputValue_Current_u8[1] = OutputValue_Current_u16 & 0xFF;
	printf("Test:Modify Currnet Value. %f. to Hex:%X%X.\r\n",OutputValue_Current_f, OutputValue_Current_u8[0],OutputValue_Current_u8[1]);
	Modify_Set_Voltage_Value(OutputValue_Current_u8);

}

/**
 * @brief 返回浮点数电流值
 * @return 浮点数电流值
 */

float Read_PV_Current_f(void)
{
	return PV_Current;
}

