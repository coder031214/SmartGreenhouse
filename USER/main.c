#include "FreeRTOS.h"
#include "task.h"
#include "lcd_task.h"
#include "getsensor_task.h"
#include "actuator_task.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "motor.h"
#include "usart2.h"
#include "esp.h"
//任务优先级
#define START_TASK_PRIO   1
//任务堆栈大小 
#define START_STK_SIZE   128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LCD_TASK_PRIO    4
//任务堆栈大小 
#define LCD_STK_SIZE     50
//任务句柄
TaskHandle_t LCDTask_Handler;

	
//任务优先级
#define GETSENSOR_TASK_PRIO    2
//任务堆栈大小 
#define GETSENSOR_STK_SIZE     50
//任务句柄
TaskHandle_t GETSENSORTask_Handler;

//任务优先级
#define ACTUATOR_TASK_PRIO    3
//任务堆栈大小 
#define ACTUATOR_STK_SIZE     50
//任务句柄
TaskHandle_t ACTUATORTask_Handler;

	
	
extern Sensor_Data_t Sensor_Data;

int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置系统中断优先级分组4
		delay_init();  //延时函数初始化
		uart_init(115200);	//串口初始化
		sensor_init();	//传感器初始化
		actuator_init(); //执行器初始化
		lcd_init(); //显示器初始化
		USART2_Init(115200);	//初始化串口	
		
		//创建任务开始
		xTaskCreate((TaskFunction_t )start_task,           //任务函数
								(const char*   )"start_task",          //任务名称
								(uint16_t      )START_STK_SIZE,        //任务堆栈大小
								(void*         )NULL,					       	 //传递给任务函数的参数
								(UBaseType_t   )START_TASK_PRIO,       //任务优先级
								(TaskHandle_t* )&StartTask_Handler);   //任务句柄
		vTaskStartScheduler();      //开启任务调度						
}

//开始任务函数  
void start_task(void *pvParameters)
{
		taskENTER_CRITICAL();     //进入临界区
		//创建LCD任务
		xTaskCreate((TaskFunction_t )lcd_task, 
								(const char*   )"lcd_task",          //任务名称
								(uint16_t      )LCD_STK_SIZE,        //任务堆栈大小
								(void*         )&Sensor_Data,					       //传递给任务函数的参数
								(UBaseType_t   )LCD_TASK_PRIO,       //任务优先级
								(TaskHandle_t* )&LCDTask_Handler);   //任务句柄
		//创建GETSENSOR任务
		xTaskCreate((TaskFunction_t )getsensor_task, 
								(const char*   )"getsensor_task",          //任务名称
								(uint16_t      )GETSENSOR_STK_SIZE,        //任务堆栈大小
								(void*         )&Sensor_Data,					       	//传递给任务函数的参数
								(UBaseType_t   )GETSENSOR_TASK_PRIO,       //任务优先级
								(TaskHandle_t* )&GETSENSORTask_Handler);   //任务句柄
		//创建ACTUATOR任务
		xTaskCreate((TaskFunction_t )actuator_task, 
								(const char*   )"actuator_task",          //任务名称
								(uint16_t      )ACTUATOR_STK_SIZE,        //任务堆栈大小
								(void*         )&Sensor_Data,					       	//传递给任务函数的参数
								(UBaseType_t   )ACTUATOR_TASK_PRIO,       //任务优先级
								(TaskHandle_t* )&ACTUATORTask_Handler);   //任务句柄						
		vTaskDelete(StartTask_Handler);    //删除开始任务
		taskEXIT_CRITICAL();   //推出临界区 						
}




