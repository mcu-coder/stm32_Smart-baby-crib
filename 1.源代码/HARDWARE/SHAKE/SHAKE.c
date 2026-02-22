#include "SHAKE.h"

uint16_t shakeData;//存放传感器状态

void SHAKE_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(SHAKE_GPIO_CLK, ENABLE);	// 打开GPIOA时钟
    
    GPIO_InitStructure.GPIO_Pin = SHAKE_GPIO_PIN;	// 配置PA0和PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);				// 一次初始化GPIOA的PA0和PA1
}


// 新增：获取PA2状态
uint16_t SHAKE_GetData(void)
{
    shakeData = !GPIO_ReadInputDataBit(SHAKE_GPIO_PORT, SHAKE_GPIO_PIN);
    return shakeData;
}
