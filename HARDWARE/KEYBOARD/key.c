#include "stm32f10x.h"              
#include "key.h"   
#include "delay.h" 
#include "usart.h"
#include "led.h"

int key_value = 0;
int fan_level;	//���ȵ�λ

void key_1_init(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;  
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);             //��ʼ��PB 0134 Ϊ��������
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOF,&GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF,&GPIO_InitStruct);             //��ʼ��PB 5678 Ϊ�������
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
	
}
 
void key_board_exti_init(void)
{	
 
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_ClearITPendingBit(EXTI_Line1);
	EXTI_ClearITPendingBit(EXTI_Line2);
	EXTI_ClearITPendingBit(EXTI_Line3);
	
	//�жϳ�ʼ��
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);


	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource1);
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStruct);
 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource2);
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStruct);
 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource3);
	EXTI_InitStruct.EXTI_Line = EXTI_Line3;
	EXTI_Init(&EXTI_InitStruct);
 
	//���ȼ�
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
 
}
 
void key_2_init(void){
	GPIO_InitTypeDef GPIO_InitStruct;

    //��ʼ��PF 0123 Ϊ�������
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;  
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);             
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOF,&GPIO_InitStruct);	
	
	//��ʼ��PF 4567 Ϊ�������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF,&GPIO_InitStruct);             
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOF,&GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);
}
 
void EXTI0_IRQHandler(void)
{
	delay_xms(10);    //����
	if(in_1==0){
		key_2_init();
		
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)
			key_value = 16;      //����16
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)
			key_value = 15;      //����15
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)
			key_value = 14;      //����14
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)==0)
			key_value = 13;      //����13
		printf("����ֵΪ��%d\r\n",key_value);
		key_1_init();
	}
	key_value=0;     //��ȡ����ֵ������
	EXTI_ClearITPendingBit(EXTI_Line0); //����жϱ�־λ
}

void EXTI1_IRQHandler(void)
{
	delay_xms(10);    //����
	if(in_2==0)
	{
		key_2_init();
		
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)
			key_value = 12;      //����12
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)
			key_value = 11;      //����11
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)
			key_value = 10;      //����10
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)==0)
			key_value = 9;      //����9
		printf("����ֵΪ��%d\r\n",key_value);  	
		key_1_init();
	}
	key_value=0;
	EXTI_ClearITPendingBit(EXTI_Line1); //����жϱ�־λ
}

void EXTI2_IRQHandler(void)
{
	delay_xms(10);    //����
	if(in_3==0){
		key_2_init();
		
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)
		{
			key_value = 8;      //����8
			led_change(close_all);	//�ر����еƹ�
		}
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)
		{
			key_value = 7;      //����7
			led_change(red);	//��ƿ���
		}	
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)
		{
			key_value = 6;      //����6
			led_change(yellow);	//�Ƶƿ���
		}		
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)==0)
		{
			key_value = 5;      //����5
			led_change(green);	//�̵ƿ���
		}
		key_1_init();
	}
	key_value=0;
	EXTI_ClearITPendingBit(EXTI_Line2); //����жϱ�־λ
}

void EXTI3_IRQHandler(void)
{
	delay_xms(10);    //����
	if(in_4==0){
		key_2_init();
		
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)
		{
			key_value = 4; //����4
			fan_level=4;	//�����ĵ�
		}
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)
		{
			key_value = 3; //����3
			fan_level=3;	//��������
		}
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)
		{
			key_value = 2; //����2
			fan_level=2; //���ȶ���
		}
		else if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)==0)
		{
			key_value = 1; //����1
			fan_level=1; //����һ��
		}
		printf("����ֵΪ��%d\r\n",key_value);
		key_1_init();
	}
	key_value=0;
	EXTI_ClearITPendingBit(EXTI_Line3); //����жϱ�־λ
}



