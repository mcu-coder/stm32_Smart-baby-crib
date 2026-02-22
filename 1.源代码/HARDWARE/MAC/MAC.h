#ifndef __MAC_H
#define	__MAC_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/***************根据自己需求更改****************/
// MAC GPIO宏定义

#define		MAC_GPIO_CLK								RCC_APB2Periph_GPIOA

// PA1 传感器定义  
#define 	MAC_GPIO1_PORT							GPIOA
#define 	MAC_GPIO1_PIN							GPIO_Pin_0

/*********************END**********************/

// 函数声明
void MAC_Init(void);
uint16_t MAC_GetData(void);          // 获取PA1出入状态
#endif /* __HW_H */
