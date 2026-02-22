#ifndef	__MODULES_H_
#define __MODULES_H_

#include "stm32f10x.h"                  // Device header
#include "adcx.h"
#include "usart3.h"
#include "rain.h"
#include "MAC.h"
#include "SHAKE.h"
#include "dht11.h"

extern u32 dat;
extern u16 co2Data;//二氧化碳变量

typedef struct
{
	uint8_t temp;
	uint8_t humi;
	uint8_t voice;
	uint8_t strike;
	uint8_t rain;
	
}SensorModules;

typedef struct
{
	uint8_t tempValue_L;
	uint8_t tempValue_H;
	uint8_t humiValue;
	
	
}SensorThresholdValue;

typedef struct
{
	uint8_t Fan_Flag;
	uint8_t Beep_Flag;
  uint8_t Jdq_Flag;
	uint8_t Curtain_Flag;
	uint8_t NOW_Curtain_Flag;
	uint8_t Music_Flag;
	
}DriveModules;
 	

extern SensorModules sensorData;			//声明传感器模块的结构体变量
extern SensorThresholdValue Sensorthreshold;	//声明传感器阈值结构体变量
extern DriveModules driveData;				//声明驱动器状态的结构体变量
void SensorScan(void);

#endif
