#ifndef __GETSENSOR_TASK_H
#define __GETSENSOR_TASK_H
#include "sys.h"

typedef struct
{	
	int air_temprature;	//空气温度
	int air_humidity;	//空气湿度
	u32 CO2_level;	//二氧化碳浓度
	u32 TVOC_levle;	//甲醛浓度
	int soil_temprature; //土壤温度
	float soil_humidity;	//土壤湿度
	float soil_PH_level; //土壤PH值
	int light_intensity; //光照强度
	int fan_speed;	//风扇转速

}Sensor_Data_t;



void sensor_init(void);	//传感器初始化
void getsensor_task(Sensor_Data_t *Sensor_Data);


#endif
