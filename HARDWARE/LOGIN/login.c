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


int Acc_AND_Pass_RIGHT; //0����δ����ɹ���1�������ɹ� 
extern int key_value;

void Login_LCD_Show() //�������
{
	POINT_COLOR=BLUE;
	Show_Str(48,20,200,24,"�ǻ�ũҵϵͳ",24,0); 
	POINT_COLOR=BLACK;
	Show_Str(15,100,200,16,"�˺ţ�",16,0);
	Show_Str(15,140,200,16,"���룺",16,0);

}

void Login_Verify() //������֤
{
	char Account[4]={'1','2','3','4'}; //��ȷ�˺�
	char Password[4]={'4','3','2','1'}; //��ȷ����
	char Login_Account[10]; //������˺�
	char Login_Password[10]; //���������
	int Input_Acc_OR_Pass; //�����˺Ż������־λ��0�������������˺ţ�1����������������
	if(Input_Acc_OR_Pass==0) //�����˺�
	{
		int i;
		for(i=0;i<10;i++)
		{
			Login_Account[i++]=key_value;
			key_value=0;
		}
		
	}	
	else if(Input_Acc_OR_Pass==1) //��������
	{
		int i;
		for(i=0;i<10;i++)
		{
			Login_Password[i++]=key_value;
			key_value=0;
		}
		
	}
	
}

