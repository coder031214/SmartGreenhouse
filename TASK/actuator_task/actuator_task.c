#include "actuator_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "motor.h"
#include "delay.h"
#include "usart2.h"
#include "esp.h"

//������̳�ʼ��
void keys_init()
{
	key_1_init();
	key_board_exti_init();
	key_2_init();
}

//ִ������ʼ��
void actuator_init()
{
	keys_init();	//������̳�ʼ��
	TIM3_PWM_Init(899,0);  //�����ʼ��
	
}

extern int key_value;
extern int fan_level;
//ִ����������
void actuator_task(Sensor_Data_t *Sensor_Data)
{
	
		//����wifl	
	while(1)
	{
		
		int j;
		if(j++%1000==0)Esp_PUB();
		
		if(fan_level==1)	//����һ��
		{
			Sensor_Data->fan_speed=1;
			TIM_SetCompare2(TIM3,350);
		}
		else if(fan_level==2) //���ȶ���
		{
			Sensor_Data->fan_speed=2;
			TIM_SetCompare2(TIM3,200);
		}
		else if(fan_level==3) //��������
		{
			Sensor_Data->fan_speed=3;
			TIM_SetCompare2(TIM3,0);
		}
		else if(fan_level==4) //����ֹͣ
		{
			Sensor_Data->fan_speed=0;
			TIM_SetCompare2(TIM3,1000);
		}
		
		vTaskDelay(500);
	}
}


