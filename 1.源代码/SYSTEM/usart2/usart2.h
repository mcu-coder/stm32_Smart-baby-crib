#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "sys.h"



void USART2_Config(void);
void Usart2_Init(unsigned int baud);			//串口2初始化
void USART2_Clear(void);									//串口2清除缓存
_Bool USART2_WaitRecive(void);						//串口2等待接收完成
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);		//发送数据
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);		//发送数据


#endif


