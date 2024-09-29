#include "led.h"
#include "gpio.h"

void led_init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //黄灯-->PE.0 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_0); 						 //PE.0 输出低
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //绿灯-->PE.1 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_1); 						 //PE.1 输出低

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //红灯-->PE.2 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOE,GPIO_Pin_2); 						 //PE.2 输出低	
}

void led_change(enum led_color color)	//开关不同颜色的灯
{
	if(color==yellow)	LED_YELLOW=!LED_YELLOW;	
	else if(color==green) LED_GREEN=!LED_GREEN;
	else if(color==red) LED_RED=!LED_RED;
	else if(color==close_all) 	//关闭所以灯光
	{
		LED_YELLOW=0;
		LED_RED=0;
		LED_GREEN=0;
	}
}

