#ifndef __ACTUATOR_TASK_H
#define __ACTUATOR_TASK_H
#include "sys.h"
#include "getsensor_task.h"


void keys_init(void);	//������̳�ʼ��
void actuator_init(void); //ִ������ʼ��
void actuator_task(Sensor_Data_t *Sensor_Data);


#endif
