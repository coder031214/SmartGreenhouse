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

//矩阵键盘初始化
void keys_init()
{
	key_1_init();
	key_board_exti_init();
	key_2_init();
}

//执行器初始化
void actuator_init()
{
	keys_init();	//矩阵键盘初始化
	TIM3_PWM_Init(899,0);  //电机初始化
	
}

extern int key_value;
extern int fan_level;
//执行器任务函数
void actuator_task(Sensor_Data_t *Sensor_Data)
{
	
		//连接wifl	
	while(1)
	{
		
		int j;
		if(j++%1000==0)Esp_PUB();
		
		if(fan_level==1)	//风扇一档
		{
			Sensor_Data->fan_speed=1;
			TIM_SetCompare2(TIM3,350);
		}
		else if(fan_level==2) //风扇二档
		{
			Sensor_Data->fan_speed=2;
			TIM_SetCompare2(TIM3,200);
		}
		else if(fan_level==3) //风扇三档
		{
			Sensor_Data->fan_speed=3;
			TIM_SetCompare2(TIM3,0);
		}
		else if(fan_level==4) //风扇停止
		{
			Sensor_Data->fan_speed=0;
			TIM_SetCompare2(TIM3,1000);
		}
		
		vTaskDelay(500);
	}
}


