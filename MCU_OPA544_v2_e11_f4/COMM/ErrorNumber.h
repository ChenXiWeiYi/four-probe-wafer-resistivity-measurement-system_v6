#ifndef ErrorNumber_H
#define ErrorNumber_H

typedef enum{
	Error_UnknownOperation			= 0x00,			// 未知上位机指令
	Error_UnknownMeasureDirection	= 0x01,	// 未知测量方向
	Error_VoltageRangeError			= 0x02,			// 电压档位错误
	Error_CRCError					= 0x03,	// CRC校验失败
	Error_UnknownCurrentPosition	= 0x04,	// 未知电流档位
	Error_NoSuitMeasPos				= 0x05,	// 没有合适的档位组合
	Error_UnderRange				= 0x06,	// 电流最大电压最小也不行
	Error_UpRange					= 0x07	// 电流最小电压最大也不行
}ErrorNumber_TypeDef;

#endif
