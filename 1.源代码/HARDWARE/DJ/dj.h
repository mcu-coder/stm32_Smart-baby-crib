#ifndef __JD_H
#define	__JD_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"



/***************根据自己需求更改****************/
// 继电器模块 GPIO宏定义

#define	JD_CLK							RCC_APB2Periph_GPIOB

#define JD_GPIO_PIN 				GPIO_Pin_5

#define JD_GPIO_PORT 				GPIOB

#define JD_ON 		GPIO_SetBits(JD_GPIO_PORT,JD_GPIO_PIN)
#define JD_OFF 	  GPIO_ResetBits(JD_GPIO_PORT,JD_GPIO_PIN)

/*********************END**********************/

void JD_Init(void);

#endif



