#ifndef __BUMP_H
#define	__BUMP_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"


/***************根据自己需求更改****************/
// 水泵1模块 GPIO宏定义

#define	BUMP1_CLK							RCC_APB2Periph_GPIOB

#define BUMP1_GPIO_PIN 				GPIO_Pin_3

#define BUMP1_GPIO_PROT 				GPIOB

#define BUMP1_ON 		GPIO_SetBits(BUMP1_GPIO_PROT,BUMP1_GPIO_PIN)
#define BUMP1_OFF 		GPIO_ResetBits(BUMP1_GPIO_PROT,BUMP1_GPIO_PIN)
// 水泵2模块 GPIO宏
#define	BUMP2_CLK							RCC_APB2Periph_GPIOB

#define BUMP2_GPIO_PIN 				GPIO_Pin_4

#define BUMP2_GPIO_PROT 				GPIOB

#define BUMP2_ON 		GPIO_SetBits(BUMP2_GPIO_PROT,BUMP2_GPIO_PIN)
#define BUMP2_OFF 		GPIO_ResetBits(BUMP2_GPIO_PROT,BUMP2_GPIO_PIN)

/*********************END**********************/

void BUMP1_Init(void);
void BUMP2_Init(void);
#endif



