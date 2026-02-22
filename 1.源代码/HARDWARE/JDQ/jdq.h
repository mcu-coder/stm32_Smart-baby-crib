#ifndef __JDQ_H
#define	__JDQ_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"



/***************根据自己需求更改****************/
// 继电器模块 GPIO宏定义

#define	JDQ_CLK							RCC_APB2Periph_GPIOB

#define JDQ_GPIO_PIN 				GPIO_Pin_1

#define JDQ_GPIO_PORT 				GPIOB

#define JDQ_ON 		GPIO_SetBits(JDQ_GPIO_PORT,JDQ_GPIO_PIN)
#define JDQ_OFF 	GPIO_ResetBits(JDQ_GPIO_PORT,JDQ_GPIO_PIN)

/*********************END**********************/

void JDQ_Init(void);

#endif



