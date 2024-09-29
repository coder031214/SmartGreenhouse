#ifndef __GETSENSOR_TASK_H
#define __GETSENSOR_TASK_H
#include "sys.h"

typedef struct
{	
	int air_temprature;	//�����¶�
	int air_humidity;	//����ʪ��
	u32 CO2_level;	//������̼Ũ��
	u32 TVOC_levle;	//��ȩŨ��
	int soil_temprature; //�����¶�
	float soil_humidity;	//����ʪ��
	float soil_PH_level; //����PHֵ
	int light_intensity; //����ǿ��
	int fan_speed;	//����ת��

}Sensor_Data_t;



void sensor_init(void);	//��������ʼ��
void getsensor_task(Sensor_Data_t *Sensor_Data);


#endif
