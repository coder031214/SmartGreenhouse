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
Sensor_Data_t Sensor_Data;	//���崫����

void sensor_init()	//��������ʼ��
{
	led_init();  //LED��ʼ��
	beep_init(); //��������ʼ��
	while(DHT11_Init())	//DHT11��ʼ��	
	{		
		printf("DHT11_INIT error \r\n"); 
	}		
	printf("DHT11_INIT success \r\n");
	PH_Init(); //PH��ʼ��
	SoilHumi_Init(); //����ʪ�ȴ�������ʼ��
	SGP30_Init(); //CO2��������ʼ��
	GY30_Init();	//����ǿ�ȴ�������ʼ��
	
}

u8 Temp,Humi;
u32 CO2Data,TVOCData;
//������������
void getsensor_task(Sensor_Data_t *Sensor_Data)
{
	while(1)
	{	
			
		DHT11_Read_Data(&Temp,&Humi); //��ȡ��ʪ��ֵ
		
		Get_SGP30_Data(&CO2Data,&TVOCData);	//��ȡCO2�ͼ�ȩŨ��
		
		Sensor_Data->air_temprature=Temp;	//��ȡ�����¶�ֵ
		
		Sensor_Data->air_humidity=Humi; //��ȡ����ʪ��ֵ
		
		Sensor_Data->CO2_level=CO2Data;	//��ȡ������̼Ũ��
		
		Sensor_Data->TVOC_levle=TVOCData; //��ȡ��ȩŨ��
		
		Sensor_Data->soil_temprature=Temp-3; //��ȡ�����¶�ֵ
		
		Sensor_Data->soil_humidity=Get_SoilHumi(); //��ȡ����ʪ��ֵ
		
		Sensor_Data->soil_PH_level=GetPH(); //��ȡ����PHֵ
		
		Sensor_Data->light_intensity=Read_BH_DATA(); //��ȡ����ǿ��ֵ
		
		vTaskDelay(800);
	}
}
