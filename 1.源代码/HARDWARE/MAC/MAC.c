#include "MAC.h"

uint16_t macData;//存放传感器状态

void MAC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(MAC_GPIO_CLK, ENABLE);	// 打开GPIOA时钟
    
    GPIO_InitStructure.GPIO_Pin = MAC_GPIO1_PIN;	// 配置PA0和PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 设置为上拉输入
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);				// 一次初始化GPIOA的PA0和PA1
}


// 新增：获取PA0状态
uint16_t MAC_GetData(void)
{
    macData = !GPIO_ReadInputDataBit(MAC_GPIO1_PORT, MAC_GPIO1_PIN);
    return macData;
}
