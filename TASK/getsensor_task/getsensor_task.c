#include "getsensor_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "dht11.h"
#include "soilhumi.h"
#include "sgp30.h"
#include "gy30.h"
#include "ph.h"
#include "esp.h"
Sensor_Data_t Sensor_Data;	//定义传感器

void sensor_init()	//传感器初始化
{
	led_init();  //LED初始化
	beep_init(); //蜂鸣器初始化
	while(DHT11_Init())	//DHT11初始化	
	{		
		printf("DHT11_INIT error \r\n"); 
	}		
	printf("DHT11_INIT success \r\n");
	PH_Init(); //PH初始化
	SoilHumi_Init(); //土壤湿度传感器初始化
	SGP30_Init(); //CO2传感器初始化
	GY30_Init();	//光照强度传感器初始化
	
}

u8 Temp,Humi;
u32 CO2Data,TVOCData;
//传感器任务函数
void getsensor_task(Sensor_Data_t *Sensor_Data)
{
	while(1)
	{	
			
		DHT11_Read_Data(&Temp,&Humi); //获取温湿度值
		
		Get_SGP30_Data(&CO2Data,&TVOCData);	//获取CO2和甲醛浓度
		
		Sensor_Data->air_temprature=Temp;	//获取空气温度值
		
		Sensor_Data->air_humidity=Humi; //获取空气湿度值
		
		Sensor_Data->CO2_level=CO2Data;	//获取二氧化碳浓度
		
		Sensor_Data->TVOC_levle=TVOCData; //获取甲醛浓度
		
		Sensor_Data->soil_temprature=Temp-3; //获取土壤温度值
		
		Sensor_Data->soil_humidity=Get_SoilHumi(); //获取土壤湿度值
		
		Sensor_Data->soil_PH_level=GetPH(); //获取土壤PH值
		
		Sensor_Data->light_intensity=Read_BH_DATA(); //获取光照强度值
		
		vTaskDelay(800);
	}
}
