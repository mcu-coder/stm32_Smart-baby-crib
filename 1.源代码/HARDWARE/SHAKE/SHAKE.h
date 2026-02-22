#ifndef __SHAKE_H
#define	__SHAKE_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/***************根据自己需求更改****************/
// MAC GPIO宏定义

#define		SHAKE_GPIO_CLK								RCC_APB2Periph_GPIOA

// PA1 传感器定义  
#define 	SHAKE_GPIO_PORT							GPIOA
#define 	SHAKE_GPIO_PIN							GPIO_Pin_4

/*********************END**********************/

// 函数声明
void SHAKE_Init(void);
uint16_t SHAKE_GetData(void);          // 获取PA1出入状态
#endif /* __HW_H */
