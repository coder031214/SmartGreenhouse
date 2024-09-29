#include "beep.h"
#include "stm32f10x.h"
#include "delay.h"

void beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PB.8,���ö˿�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ�Ϊ50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIOB.8
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);//���0���رշ��������
}

void beep_play(int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		BEEP=1;
		delay_ms(200);
		BEEP=0;
	}
}

