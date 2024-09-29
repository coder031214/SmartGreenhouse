#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "delay.h"
#include "usart.h"    
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "key.h"
#include "usart.h"


int Acc_AND_Pass_RIGHT; //0代表未登入成功，1代表登入成功 
extern int key_value;

void Login_LCD_Show() //登入界面
{
	POINT_COLOR=BLUE;
	Show_Str(48,20,200,24,"智慧农业系统",24,0); 
	POINT_COLOR=BLACK;
	Show_Str(15,100,200,16,"账号：",16,0);
	Show_Str(15,140,200,16,"密码：",16,0);

}

void Login_Verify() //登入验证
{
	char Account[4]={'1','2','3','4'}; //正确账号
	char Password[4]={'4','3','2','1'}; //正确密码
	char Login_Account[10]; //输入的账号
	char Login_Password[10]; //输入的密码
	int Input_Acc_OR_Pass; //输入账号或密码标志位，0代表正在输入账号，1代表正在输入密码
	if(Input_Acc_OR_Pass==0) //输入账号
	{
		int i;
		for(i=0;i<10;i++)
		{
			Login_Account[i++]=key_value;
			key_value=0;
		}
		
	}	
	else if(Input_Acc_OR_Pass==1) //输入密码
	{
		int i;
		for(i=0;i<10;i++)
		{
			Login_Password[i++]=key_value;
			key_value=0;
		}
		
	}
	
}

