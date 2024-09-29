#include "led.h"
#include "gpio.h"

void led_init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //�Ƶ�-->PE.0 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_0); 						 //PE.0 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //�̵�-->PE.1 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_1); 						 //PE.1 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //���-->PE.2 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_2); 						 //PE.2 �����	
}

void led_change(enum led_color color)	//���ز�ͬ��ɫ�ĵ�
{
	if(color==yellow)	LED_YELLOW=!LED_YELLOW;	
	else if(color==green) LED_GREEN=!LED_GREEN;
	else if(color==red) LED_RED=!LED_RED;
	else if(color==close_all) 	//�ر����Եƹ�
	{
		LED_YELLOW=0;
		LED_RED=0;
		LED_GREEN=0;
	}
}

