#include "stm32f10x.h"
#include "led.h"
#include "beep.h"
#include "usart.h"
#include "usart2.h"
#include "delay.h"
#include "jdq.h"
#include "oled.h"
#include "key.h"
#include "Modules.h"
#include "TIM2.h"
#include "TIM3.h"
#include "adcx.h"
#include "flash.h"
#include "fan.h"
#include "bump.h"
#include "stepmotor.h"




#define KEY_Long1	11

#define KEY_1	1
#define KEY_2	2
#define KEY_3	3
#define KEY_4	4

#define FLASH_START_ADDR	0x0801f000	//写入的起始地址

//传感器变量声明
uint16_t time_num = 0;								//10ms计时
uint16_t count_voice=0,count_strike=0,count_music=0;

SensorModules sensorData;								//声明传感器数据结构体变量
SensorThresholdValue Sensorthreshold;		//声明传感器阈值结构体变量
DriveModules driveData;									//声明驱动器状态结构体变量
static uint8_t app_cmd = 0;   // 0 无指令  3 开  4 关
uint8_t mode = 0;	//系统模式  1自动  2手动  3设置

//系统静态变量
static uint8_t count_a = 1;  //自动模式按键数
 uint8_t count_m = 1;  //手动模式按键数
static uint8_t count_s = 1;	 //设置模式按键数

extern uint8_t usart2_buf[256];				//串口2接收数组
char display_buf[16];					        //显示数组

/**
  * @brief  显示菜单内容
  * @param  无
  * @retval 无
  */
enum 
{
	AUTO_MODE = 0,
	MANUAL_MODE,
	SETTINGS_MODE
	
}MODE_PAGES;

/**
  * @brief  显示菜单1的固定内容
  * @param  无
  * @retval 无
  */
void OLED_autoPage1(void)		//自动模式菜单第一页
{	
	//显示“温度：  ℃”
	OLED_ShowChinese(0,0,0,16,1);//温
	OLED_ShowChinese(16,0,2,16,1);//度
	OLED_ShowChar(32,0,':',16,1);
	 
	
}
void SensorDataDisplay1(void)		//传感器数据显示第一页
{                                                                                                                                                                       ;
	//显示环境温度数据
	OLED_ShowNum(40,0,sensorData.temp,2,16,1);
	//显示环境湿度数据
 
	if(sensorData.strike==1)
		OLED_ShowChinese(90,48,70,16,1);
	else
		OLED_ShowChinese(90,48,71,16,1);
}

/**
  * @brief  显示手动模式设置界面1
  * @param  无
  * @retval 无
  */
void OLED_manualPage1(void)
{
	//显示“风扇：”
	OLED_ShowChinese(16,0,20,16,1);	
	OLED_ShowChinese(32,0,21,16,1);	
	OLED_ShowChar(64,0,':',16,1);

	 
}



/**
  * @brief  显示手动模式设置参数界面1
  * @param  无
  * @retval 无
  */
void ManualSettingsDisplay1(void)
{
	if(driveData.Fan_Flag)
	{
		OLED_ShowChinese(96,0,24,16,1); 	//开
	}
	else
	{
		OLED_ShowChinese(96,0,26,16,1); 	//关
	}
 
}


/**
  * @brief  显示系统阈值设置界面1
  * @param  无
  * @retval 无
  */
void OLED_settingsPage1(void)
{
	
	//显示“温度上限”
	OLED_ShowChinese(16,0,0,16,1);	
	OLED_ShowChinese(32,0,2,16,1);	
	OLED_ShowChinese(48,0,65,16,1);	
	OLED_ShowChinese(64,0,66,16,1);	
	OLED_ShowChar(80,0,':',16,1);
	 
	
}

void SettingsThresholdDisplay1(void)
{
	//显示温度上限数值
	OLED_ShowNum(90, 0, Sensorthreshold.tempValue_H , 2,16,1);
	 
}

/**
  * @brief  记录自动模式界面下按KEY2的次数
  * @param  无
  * @retval 返回次数
  */
uint8_t SetAuto(void)  
{
	if(KeyNum == KEY_2)
	{
		KeyNum = 0;
		count_a++;
		if (count_a > 2)
		{
			count_a = 1;
		}
		OLED_Clear();
	}
	return count_a;
}


/**
  * @brief  记录手动模式界面下按KEY2的次数
  * @param  无
  * @retval 返回次数
  */
uint8_t SetManual(void)  
{

	if(KeyNum == KEY_2)
	{
		KeyNum = 0;
		count_m++;
		if (count_m == 4)
		{
			OLED_Clear();
		}
		 
	}
	return count_m;
}

/**
  * @brief  记录阈值界面下按KEY2的次数
  * @param  无
  * @retval 返回次数
  */
uint8_t SetSelection(void)
{
	if(KeyNum == KEY_2)
	{
		KeyNum = 0;
		count_s++;
		if (count_s == 3)
		{
			OLED_Clear();
		}
	 
	}
	return count_s;
}


/**
  * @brief  显示手动模式界面的选择符号
  * @param  num 为显示的位置
  * @retval 无
  */
void OLED_manualOption(uint8_t num)
{
	switch(num)
	{
		case 1:	
			OLED_ShowChar(0, 0,'>',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
	 
		default: break;
	}
}

/**
  * @brief  显示阈值界面的选择符号
  * @param  num 为显示的位置
  * @retval 无
  */
void OLED_settingsOption(uint8_t num)
{
	switch(num)
	{
		case 1:	
			OLED_ShowChar(0, 0,'>',16,1);
			OLED_ShowChar(0,16,' ',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		case 2:	
			OLED_ShowChar(0, 0,' ',16,1);
			OLED_ShowChar(0,16,'>',16,1);
			OLED_ShowChar(0,32,' ',16,1);
			OLED_ShowChar(0,48,' ',16,1);
			break;
		 
		default: break;
	}
}

/**
  * @brief  自动模式控制函数
  * @param  无
  * @retval 无
  */
void AutoControl(void)
{
	if(sensorData.temp>Sensorthreshold.tempValue_H || sensorData.humi>Sensorthreshold.humiValue)
	{
		driveData.Fan_Flag = 1;
	}
	else
	{
		driveData.Fan_Flag = 0;
	}
	  
	if(sensorData.rain)
	{
		UsartPrintf(USART2,"婴儿尿床\r\n");
	}
}

/**
  * @brief  手动模式控制函数
  * @param  无
  * @retval 无
  */
void ManualControl(uint8_t num)
{
	if(app_cmd)
    {
        KeyNum  = app_cmd;   // 伪造一次按键值
        app_cmd = 0;         // 立即清掉，只执行一次
    }
		
	switch(num)
	{
		case 1:	
			//显示外设开关
			if(KeyNum == KEY_3)
				driveData.Fan_Flag = 1;
			if(KeyNum == KEY_4)
				driveData.Fan_Flag = 0;
			break;
		case 2:	
			if(KeyNum == KEY_3)
				driveData.Jdq_Flag = 1;
			if(KeyNum == KEY_4)
				driveData.Jdq_Flag = 0;
			break;
		 
		default: break;
	}

}

/**
  * @brief  控制函数
  * @param  无
  * @retval 无
  */
void Control_Manager(void)
{

	if(driveData.Fan_Flag)
	{
		FAN_ON;
	}
	else
	{
		FAN_OFF;
	}
	
	   

}

/**
  * @brief  阈值设置函数
  * @param  无
  * @retval 无
  */
void ThresholdSettings(uint8_t num)
{
	switch (num)
	{				
		case 1:
			if (KeyNum == KEY_3)
			{
				KeyNum = 0;
				Sensorthreshold.tempValue_H += 1;
				if (Sensorthreshold.tempValue_H > 50)
				{
					Sensorthreshold.tempValue_H = 50;
				}
			}
		 
			break;
			
		case 2:
			if (KeyNum == KEY_3)
			{
				KeyNum = 0;
				if (Sensorthreshold.tempValue_L < (Sensorthreshold.tempValue_H-1))
				{
					Sensorthreshold.tempValue_L+= 1;
				}
			}
			else if (KeyNum == KEY_4)
			{
				KeyNum = 0;
				Sensorthreshold.tempValue_L -= 1;
				if (Sensorthreshold.tempValue_L < 5)
				{
					Sensorthreshold.tempValue_L = 5;
				}				
			}
			break;
			
			 
		default: break;		
	}
}
/**
  * @brief  flash阈值读取函数
  * @param  无
  * @retval 无
  */
void FLASH_ReadThreshold()
{
	Sensorthreshold.tempValue_H	= FLASH_R(FLASH_START_ADDR);	//从指定页的地址读FLASH
	Sensorthreshold.tempValue_L = FLASH_R(FLASH_START_ADDR+2);	//从指定页的地址读FLASH
	 
}

int main(void)
{ 
  SystemInit();//配置系统时钟为72M	
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先分组
	
	//传感器初始化
	SHAKE_Init();
	MAC_Init();
	DHT11_Init();
	RAIN_Init();
	
	 
	TIM2_Init(72-1,1000-1);
	FLASH_ReadThreshold();//阈值读取函数
////	TIM3_Int_Init(1000-1,72-1);		//定时1ms中断
	OLED_Clear();//清屏
  while (1)
  {
		SensorScan();	//获取传感器数据
		time_num++;												//计时变量+1
		if(time_num >= 5000)
		{
			time_num = 0;
		}
		
		switch(mode)
		{
			case AUTO_MODE://默认自动模式
					OLED_autoPage1();	//显示主页面1固定信息
					SensorDataDisplay1();	//显示传感器1数据
				AutoControl();//自动模式控制函数
				
				/*按键1按下时切换模式*/
				if (KeyNum == KEY_1)   //系统模式mode  1自动  2手动  3设置
				{
					KeyNum = 0;
					mode = MANUAL_MODE;//进入手动模式
					count_m = 1;//手动模式下按键2的次数置一
					OLED_Clear();
				}
				 
				
				break;
				
			case MANUAL_MODE://手动模式下
				OLED_manualOption(SetManual());//手动模式光标显示函数
				ManualControl(SetManual());//手动模式控制函数
				OLED_manualPage1();//手动模式界面1显示
				ManualSettingsDisplay1();//手动模式界面1的开关显示
				
				if (KeyNum == KEY_1)   //系统模式mode  0手动  1自动（默认）
				{
					KeyNum = 0;
					mode = AUTO_MODE;//进入自动模式
					count_a = 1;//自动模式下按键2按下的次数置一
					OLED_Clear();
				}
				Control_Manager();//执行器执行函数
				
				break;
				
			case SETTINGS_MODE://阈值设置函数

				OLED_settingsOption(SetSelection());	//实现阈值设置页面的选择功能
				ThresholdSettings(SetSelection());	//实现阈值调节功能	
					
					OLED_settingsPage1();	//显示阈值设置界面1固定信息
					SettingsThresholdDisplay1();	//显示传感器阈值1数据	
					//判断是否退出阈值设置界面
					if (KeyNum == KEY_1)
					{
						KeyNum = 0;
						mode = AUTO_MODE;	//进入自动模式
						count_a = 1;//自动模式下按键2按下的次数置一
						OLED_Clear();	//清屏
						//存储修改的传感器阈值至flash内
						FLASH_W(FLASH_START_ADDR,	Sensorthreshold.tempValue_H,Sensorthreshold.tempValue_L,
						Sensorthreshold.humiValue);
					}
				break;
				default: break;
		}
		
		
		
  }
}
