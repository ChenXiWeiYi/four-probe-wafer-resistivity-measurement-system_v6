#include "USART.h"

/**
 * 增加了返回接收是否完成标志的函数,方便在main中调用
 * @author 刘嘉诚(修改)
 * @date 2025.08.31
 */


/** 变量定义 **/
UART_HandleTypeDef USART1_Handler;

static volatile bool     RxFrameReady = false;	// 接收完成标志
static uint8_t  aRxBuffer;				// HAL库中断接收USART缓冲,1B
uint8_t  RxPacket[MAX_RX_LEN];	// 接收缓冲区
volatile uint16_t RxPacketLen = 0;		// 当前帧长度

static RxState_t g_RxState = RX_STATE_WAIT_HEAD1;
static uint8_t   g_RxCounter = 0;   // 接收计数器
static uint8_t   g_BodyLen = 0;     // 解析出的后续长度

/** 标准库支持函数 */
#pragma import(__use_no_semihosting)                             
struct __FILE{ int handle;}; 
FILE __stdout;       
/**
 * @brief _sys_exit
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void _sys_exit(int x){ x = x;}	// 定义_sys_exit()以避免使用半主机模式 
/**
 * @brief fputc
 * @author 刘嘉诚
 * @date 2026.06.08
 */
int fputc(int ch, FILE *f) // 重定义fputc函数
{	
	while((USART1->SR&0x40)==0);
	USART1->DR = (u8) ch;      
	return ch;
}

/**
 * @brief USART_Init 串口初始化
 * 此处中断只接受一个数据
 * @param BaudRate_USART1 USART1的波特率
 * @author 刘嘉诚
 * @date 2025.08.31
 */
void USART_Init(uint32_t BaudRate_USART1)
{
	USART1_Handler.Instance			= USART1;
	USART1_Handler.Init.BaudRate	= BaudRate_USART1;
	USART1_Handler.Init.WordLength	= UART_WORDLENGTH_8B;	// 8b
	USART1_Handler.Init.StopBits	= UART_STOPBITS_1;		// 一个停止位
	USART1_Handler.Init.Parity		= UART_PARITY_NONE;		// 无奇偶校验位
	USART1_Handler.Init.HwFlowCtl	= UART_HWCONTROL_NONE;	// 无硬件流控
	USART1_Handler.Init.Mode		= UART_MODE_TX_RX;		// 收发模式
	HAL_UART_Init(&USART1_Handler);

	HAL_UART_Receive_IT(&USART1_Handler, &aRxBuffer, 1);
}


/**
 * @brief 被HAL_UART_Init调用,初始化USART1的GPIO和中断
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	if(huart->Instance == USART1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();

		GPIO_Initure.Pin		= GPIO_PIN_9|GPIO_PIN_10;
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;
		GPIO_Initure.Pull		= GPIO_PULLUP;
		GPIO_Initure.Speed		= GPIO_SPEED_FAST;
		GPIO_Initure.Alternate	= GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);

		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,1,0);			//抢占优先级1，子优先级0
	}
}


/** 
 * @brief HAL_UART_RxCpltCallback 回调函数
 * 帧格式: 0xAA(帧头) 0x55(帧头) 后面的长度 数据 CRC
 * @param *huart 哪个USART
 * @author 刘嘉诚
 * @date 2026.02.03
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){
		if (!RxFrameReady){	// 看main有没有读取完上一帧,没有读完的话这次的就跳过
			switch(g_RxState){
			case RX_STATE_WAIT_HEAD1:
				if(aRxBuffer == PROTOCOL_HEAD1){ // 收到 AA
					g_RxState = RX_STATE_WAIT_HEAD2;
					RxPacket[0] = aRxBuffer;
				}
				break;
			case RX_STATE_WAIT_HEAD2:
				if(aRxBuffer == PROTOCOL_HEAD2){ // 收到 55
					g_RxState = RX_STATE_WAIT_LEN;
					RxPacket[1] = aRxBuffer;
				}else{ // 0xAA后面不是0x55,一般来说不会出现这种情况,先这么写
					g_RxState = RX_STATE_WAIT_HEAD1;
				}
				break;
			case RX_STATE_WAIT_LEN:
				g_BodyLen = aRxBuffer;
				RxPacket[2] = aRxBuffer;
				if(g_BodyLen > (MAX_RX_LEN - 3)){	// 简单地判断接收到的长度是不是比缓冲区大,基本不会
					g_RxState = RX_STATE_WAIT_HEAD1; // 长度非法，重置
				}else{ // 长度ok
					g_RxState = RX_STATE_WAIT_BODY;
					g_RxCounter = 0;
				}
				break;
			case RX_STATE_WAIT_BODY:
				RxPacket[3 + g_RxCounter] = aRxBuffer;
				g_RxCounter = g_RxCounter + 1;
                if(g_RxCounter >= g_BodyLen){	// 检查是否收完了
					RxPacketLen = 3 + g_BodyLen; // 记录总长
					RxFrameReady = true;         // 置标志位
                    g_RxState = RX_STATE_WAIT_HEAD1; // 状态机归位，准备下一帧
				}
				break;
			default:
				g_RxState = RX_STATE_WAIT_HEAD1;
				break;
			}
		}

        HAL_UART_Receive_IT(&USART1_Handler, &aRxBuffer, 1);	// 重新开启中断并设置RxXferCount为1
    }
}


/**
 * @brief USART1_IRQHandler 串口1中断服务程序
 * 不再轮询超时
 * @author 刘嘉诚
 * @date 2026.02.03
 */
void USART1_IRQHandler(void)                	
{
	HAL_UART_IRQHandler(&USART1_Handler);	//调用HAL库中断处理公用函数
}

/**
 * @brief 清除接收标志，允许接收下一帧
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void USART1_Clear_Rx(void)
{
    RxFrameReady = false;
}

/**
 * @brief 查询是否接收完成
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool is_USART1_RxOK(void)
{
    return RxFrameReady;
}
