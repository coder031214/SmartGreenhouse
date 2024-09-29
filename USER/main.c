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
//�������ȼ�
#define START_TASK_PRIO   1
//�����ջ��С 
#define START_STK_SIZE   128
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LCD_TASK_PRIO    4
//�����ջ��С 
#define LCD_STK_SIZE     50
//������
TaskHandle_t LCDTask_Handler;

	
//�������ȼ�
#define GETSENSOR_TASK_PRIO    2
//�����ջ��С 
#define GETSENSOR_STK_SIZE     50
//������
TaskHandle_t GETSENSORTask_Handler;

//�������ȼ�
#define ACTUATOR_TASK_PRIO    3
//�����ջ��С 
#define ACTUATOR_STK_SIZE     50
//������
TaskHandle_t ACTUATORTask_Handler;

	
	
extern Sensor_Data_t Sensor_Data;

int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ�ж����ȼ�����4
		delay_init();  //��ʱ������ʼ��
		uart_init(115200);	//���ڳ�ʼ��
		sensor_init();	//��������ʼ��
		actuator_init(); //ִ������ʼ��
		lcd_init(); //��ʾ����ʼ��
		USART2_Init(115200);	//��ʼ������	
		
		//��������ʼ
		xTaskCreate((TaskFunction_t )start_task,           //������
								(const char*   )"start_task",          //��������
								(uint16_t      )START_STK_SIZE,        //�����ջ��С
								(void*         )NULL,					       	 //���ݸ��������Ĳ���
								(UBaseType_t   )START_TASK_PRIO,       //�������ȼ�
								(TaskHandle_t* )&StartTask_Handler);   //������
		vTaskStartScheduler();      //�����������						
}

//��ʼ������  
void start_task(void *pvParameters)
{
		taskENTER_CRITICAL();     //�����ٽ���
		//����LCD����
		xTaskCreate((TaskFunction_t )lcd_task, 
								(const char*   )"lcd_task",          //��������
								(uint16_t      )LCD_STK_SIZE,        //�����ջ��С
								(void*         )&Sensor_Data,					       //���ݸ��������Ĳ���
								(UBaseType_t   )LCD_TASK_PRIO,       //�������ȼ�
								(TaskHandle_t* )&LCDTask_Handler);   //������
		//����GETSENSOR����
		xTaskCreate((TaskFunction_t )getsensor_task, 
								(const char*   )"getsensor_task",          //��������
								(uint16_t      )GETSENSOR_STK_SIZE,        //�����ջ��С
								(void*         )&Sensor_Data,					       	//���ݸ��������Ĳ���
								(UBaseType_t   )GETSENSOR_TASK_PRIO,       //�������ȼ�
								(TaskHandle_t* )&GETSENSORTask_Handler);   //������
		//����ACTUATOR����
		xTaskCreate((TaskFunction_t )actuator_task, 
								(const char*   )"actuator_task",          //��������
								(uint16_t      )ACTUATOR_STK_SIZE,        //�����ջ��С
								(void*         )&Sensor_Data,					       	//���ݸ��������Ĳ���
								(UBaseType_t   )ACTUATOR_TASK_PRIO,       //�������ȼ�
								(TaskHandle_t* )&ACTUATORTask_Handler);   //������						
		vTaskDelete(StartTask_Handler);    //ɾ����ʼ����
		taskEXIT_CRITICAL();   //�Ƴ��ٽ��� 						
}




