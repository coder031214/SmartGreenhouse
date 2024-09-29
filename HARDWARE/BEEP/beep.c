#include "beep.h"
#include "stm32f10x.h"
#include "delay.h"

void beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PB.8,配置端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //速度为50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIOB.8
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
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

