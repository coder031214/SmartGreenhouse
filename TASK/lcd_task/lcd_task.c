#include "FreeRTOS.h"
#include "task.h"
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h" 
#include "touch.h"
#include "24cxx.h"
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "delay.h"
#include "usart.h"    
#include "lcd_task.h"
#include "getsensor_task.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "login.h"
#include "esp.h"

void lcd_init()
{
	LCD_Init();  			  //LCD��ʼ��
	LCD_Chinese_Init(); //�����ֿ��ʼ��
	tp_dev.init();      //LCD������ʼ��
	lcd_draw_start();	  //LCD��ʼ����	
}

extern int Acc_AND_Pass_RIGHT;
void lcd_draw_start(void )
{	
//		while(Acc_AND_Pass_RIGHT==0)
//		{
//			Login_LCD_Show(); //�������
//		if(tp_dev.sta&TP_PRES_DOWN)			//������������
//			{	
//				LCD_Clear(WHITE);	//���	  			   
//			}//else beep_play(1);	//û�а��µ�ʱ�� 
//		}
		
		POINT_COLOR=MAGENTA;
    LCD_Clear(WHITE);
		LCD_ShowString(20,100,200,24,24,"Smart agriculture");		//���ؽ���
		LCD_ShowString(20,140,200,24,24,"Loading.");
		delay_ms(400);
	  LCD_ShowString(115,140,200,24,24,".");
		delay_ms(400);
    LCD_ShowString(125,140,200,24,24,".");
		delay_ms(400);
		LCD_ShowString(135,140,200,24,24,".");
		delay_ms(400);
		LCD_ShowString(145,140,200,24,24,".");
		delay_ms(400);
		LCD_ShowString(155,140,200,24,24,".");
		delay_ms(400);
//	  beep_play(1);
	
		POINT_COLOR=RED;
    LCD_Clear(WHITE);	
	
		LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
	
		Show_Str(48,0,200,24,"�ǻ�ũҵϵͳ",24,0);
	
		POINT_COLOR=BLACK;
		
	  Show_Str(15,40,200,16,"�����¶ȣ�",16,0); //�����¶�
		Show_Str(125,40,200,16,"��",16,0);
		
		Show_Str(15,60,200,16,"����ʪ�ȣ�",16,0); //����ʪ��
		LCD_ShowString(125,60,150,12,16,"%RH");
	
		Show_Str(15,80,200,16,"CO2Ũ�ȣ�",16,0); //CO2Ũ��
		LCD_ShowString(125,80,150,12,16,"ppm");
	
		Show_Str(15,100,200,16,"��ȩŨ�ȣ�",16,0);	//��ȩŨ��
		LCD_ShowString(125,100,150,12,16,"ppd");
		
		Show_Str(15,120,200,16,"�����¶ȣ�",16,0); //�����¶�
		Show_Str(125,120,200,16,"��",16,0);
	
		Show_Str(15,140,200,16,"����ʪ�ȣ�",16,0); //����ʪ��
		LCD_ShowString(125,140,150,12,16,"%");
	
		Show_Str(15,160,200,16,"����PHֵ��",16,0); //����PHֵ
	
		Show_Str(15,180,200,16,"����ǿ�ȣ�",16,0); //����ǿ��
		LCD_ShowString(125,180,150,12,16,"Lux");

		Show_Str(15,220,200,16,"����ת�٣�",16,0); //����ת��
}


//��ʾ��������
void lcd_task(Sensor_Data_t *Sensor_Data)
{
	
	while(1)
	{
		
		LCD_ShowxNum(85,40,(u8)Sensor_Data->air_temprature,4,16,0x00);  //�����¶�
		
		LCD_ShowxNum(85,60,(u8)Sensor_Data->air_humidity,4,16,0x00);  //����ʪ��
				
		LCD_ShowxNum(85,80,(u32)Sensor_Data->CO2_level,4,16,0x00);  //CO2Ũ��
		
		LCD_ShowxNum(85,100,(u32)Sensor_Data->TVOC_levle,4,16,0x00);  //��ȩŨ��
		
		LCD_ShowxNum(85,120,(u8)Sensor_Data->soil_temprature,4,16,0x00);  //����ʪ��
		
		LCD_ShowxNum(85,140,(float)Sensor_Data->soil_humidity,4,16,0x00);  //����ʪ��
		
		LCD_ShowxNum(85,160,(float)Sensor_Data->soil_PH_level,4,16,0x00);  //����PHֵ		
		
		LCD_ShowxNum(85,180,(u16)Sensor_Data->light_intensity,4,16,0x00);  //����ǿ��	
		
		if(Sensor_Data->fan_speed==0)	//�����ٶ�
		{
			LCD_Fill(96, 16*14, 144, 16*14.8, LIGHTBLUE); //���ȹر�
		}
		else if(Sensor_Data->fan_speed==1)
		{
			LCD_Fill(96, 16*14, 112, 16*14.8, GREEN);  //����һ�������ɫ
			LCD_Fill(112, 16*14, 144, 16*14.8, GRAYBLUE); 
		}
		else if(Sensor_Data->fan_speed==2)
		{
			LCD_Fill(112, 16*14, 128, 16*14.8, YELLOW); //���ȶ�������ɫ
			LCD_Fill(96, 16*14, 112, 16*14.8, GRAYBLUE);
			LCD_Fill(128, 16*14, 144, 16*14.8, GRAYBLUE);	
		}
		else if(Sensor_Data->fan_speed==3)
		{
			LCD_Fill(128, 16*14, 144, 16*14.8, RED);  //������������ɫ
			LCD_Fill(96, 16*14, 128, 16*14.8, GRAYBLUE);
		}
		LCD_Fill(100, 16*16, 130, 16*18, DARKBLUE); //���ȹرհ�ť	    	    
		esp_Init();
		vTaskDelay(500);
	}
}





