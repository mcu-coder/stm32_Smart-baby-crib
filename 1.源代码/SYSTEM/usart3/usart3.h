#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header

extern u8 RXBUF[20];
extern u8 RXOVER;
extern u8 RXCOUNT;

void USART3_Config(void);

void USART3_IRQHandler(void);

void USART3_SendByte(uint8_t  Data); 
void Uart3_SendCMD1(int dat1, int dat2, int dat3);
void Uart3_SendCMD2(int dat1, int dat2);

void Uart3_SendCmd(int len);

void Usart3_SendString(unsigned char *str, unsigned short len);
#endif

