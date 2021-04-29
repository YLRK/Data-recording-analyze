/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-02 23:43:58
 * @LastEditTime: 2021-04-08 17:10:19
 */
#include "usart.h"
#include "usmart.h"
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA = 0; //接收状态标记

u8 aRxBuffer[RXBUFFERSIZE];		  //HAL库使用的串口接收缓冲
UART_HandleTypeDef UART3_Handler; //UART句柄

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	USART3->DR = (u8) ch;      
	return ch;
}

void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3) //如果是串口3
	{
		if ((USART_RX_STA & 0x8000) == 0) //接收未完成
		{
			if (USART_RX_STA & 0x4000) //接收到了0x0d
			{
				if (aRxBuffer[0] != 0x0a)
					USART_RX_STA = 0; //接收错误,重新开始
				else
					USART_RX_STA |= 0x8000; //接收完成了
			}
			else //还没收到0X0D
			{
				if (aRxBuffer[0] == 0x0d)
					USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = aRxBuffer[0];
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA = 0; //接收数据错误,重新开始接收
				}
			}
		}
	}
}

//串口3中断服务程序
void USART3_IRQHandler(void)
{
	u32 timeout = 0;

	HAL_UART_IRQHandler(&UART3_Handler); //调用HAL库中断处理公用函数

	timeout = 0;
	while (HAL_UART_GetState(&UART3_Handler) != HAL_UART_STATE_READY) //等待就绪
	{
		timeout++; ////超时处理
		if (timeout > HAL_MAX_DELAY)
			break;
	}

	timeout = 0;
	while (HAL_UART_Receive_IT(&UART3_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE) != HAL_OK) //一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
		timeout++; //超时处理
		if (timeout > HAL_MAX_DELAY)
			break;
	}
	HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
}


//初始化IO 串口1
//bound:波特率
int uart_init(void)
{
	//UART 初始化设置
	UART3_Handler.Instance = USART3;					//USART3
	UART3_Handler.Init.BaudRate = 115200;				//波特率
	UART3_Handler.Init.WordLength = UART_WORDLENGTH_8B; //字长为8位数据格式
	UART3_Handler.Init.StopBits = UART_STOPBITS_1;		//一个停止位
	UART3_Handler.Init.Parity = UART_PARITY_NONE;		//无奇偶校验位
	UART3_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE; //无硬件流控
	UART3_Handler.Init.Mode = UART_MODE_TX_RX;			//收发模式
	HAL_UART_Init(&UART3_Handler);						//HAL_UART_Init()会使能UART3

	HAL_UART_Receive_IT(&UART3_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE); //该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
    
	usmart_dev.init(84); 		    //初始化USMART	
	
    return RT_EOK;
}

INIT_DEVICE_EXPORT(uart_init);
