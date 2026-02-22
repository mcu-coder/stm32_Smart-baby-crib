# include "Modules.h"

/**
  * @brief  传感器数据扫描
  * @param  无
  * @retval 无
  */
uint8_t strike=1,voice =0;

void SensorScan(void)
{
		DHT11_Read_Data(&sensorData.temp, &sensorData.humi);
		sensorData.rain = RAIN_GetData();
		strike = SHAKE_GetData();
		voice = MAC_GetData();
		if(strike == 0)
			sensorData.strike = 1;
		if(voice == 1)
			sensorData.voice = 1;
		
	
}


