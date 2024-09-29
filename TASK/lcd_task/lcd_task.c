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
	LCD_Init();  			  //LCD初始化
	LCD_Chinese_Init(); //中文字库初始化
	tp_dev.init();      //LCD触屏初始化
	lcd_draw_start();	  //LCD初始画面	
}

extern int Acc_AND_Pass_RIGHT;
void lcd_draw_start(void )
{	
//		while(Acc_AND_Pass_RIGHT==0)
//		{
//			Login_LCD_Show(); //登入界面
//		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
//			{	
//				LCD_Clear(WHITE);	//清除	  			   
//			}//else beep_play(1);	//没有按下的时候 
//		}
		
		POINT_COLOR=MAGENTA;
    LCD_Clear(WHITE);
		LCD_ShowString(20,100,200,24,24,"Smart agriculture");		//加载界面
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
	
		LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
	
		Show_Str(48,0,200,24,"智慧农业系统",24,0);
	
		POINT_COLOR=BLACK;
		
	  Show_Str(15,40,200,16,"空气温度：",16,0); //空气温度
		Show_Str(125,40,200,16,"℃",16,0);
		
		Show_Str(15,60,200,16,"空气湿度：",16,0); //空气湿度
		LCD_ShowString(125,60,150,12,16,"%RH");
	
		Show_Str(15,80,200,16,"CO2浓度：",16,0); //CO2浓度
		LCD_ShowString(125,80,150,12,16,"ppm");
	
		Show_Str(15,100,200,16,"甲醛浓度：",16,0);	//甲醛浓度
		LCD_ShowString(125,100,150,12,16,"ppd");
		
		Show_Str(15,120,200,16,"土壤温度：",16,0); //土壤温度
		Show_Str(125,120,200,16,"℃",16,0);
	
		Show_Str(15,140,200,16,"土壤湿度：",16,0); //土壤湿度
		LCD_ShowString(125,140,150,12,16,"%");
	
		Show_Str(15,160,200,16,"土壤PH值：",16,0); //土壤PH值
	
		Show_Str(15,180,200,16,"光照强度：",16,0); //光照强度
		LCD_ShowString(125,180,150,12,16,"Lux");

		Show_Str(15,220,200,16,"风扇转速：",16,0); //风扇转速
}


//显示器任务函数
void lcd_task(Sensor_Data_t *Sensor_Data)
{
	
	while(1)
	{
		
		LCD_ShowxNum(85,40,(u8)Sensor_Data->air_temprature,4,16,0x00);  //空气温度
		
		LCD_ShowxNum(85,60,(u8)Sensor_Data->air_humidity,4,16,0x00);  //空气湿度
				
		LCD_ShowxNum(85,80,(u32)Sensor_Data->CO2_level,4,16,0x00);  //CO2浓度
		
		LCD_ShowxNum(85,100,(u32)Sensor_Data->TVOC_levle,4,16,0x00);  //甲醛浓度
		
		LCD_ShowxNum(85,120,(u8)Sensor_Data->soil_temprature,4,16,0x00);  //土壤湿度
		
		LCD_ShowxNum(85,140,(float)Sensor_Data->soil_humidity,4,16,0x00);  //土壤湿度
		
		LCD_ShowxNum(85,160,(float)Sensor_Data->soil_PH_level,4,16,0x00);  //土壤PH值		
		
		LCD_ShowxNum(85,180,(u16)Sensor_Data->light_intensity,4,16,0x00);  //光照强度	
		
		if(Sensor_Data->fan_speed==0)	//风扇速度
		{
			LCD_Fill(96, 16*14, 144, 16*14.8, LIGHTBLUE); //风扇关闭
		}
		else if(Sensor_Data->fan_speed==1)
		{
			LCD_Fill(96, 16*14, 112, 16*14.8, GREEN);  //风扇一档填充绿色
			LCD_Fill(112, 16*14, 144, 16*14.8, GRAYBLUE); 
		}
		else if(Sensor_Data->fan_speed==2)
		{
			LCD_Fill(112, 16*14, 128, 16*14.8, YELLOW); //风扇二档填充黄色
			LCD_Fill(96, 16*14, 112, 16*14.8, GRAYBLUE);
			LCD_Fill(128, 16*14, 144, 16*14.8, GRAYBLUE);	
		}
		else if(Sensor_Data->fan_speed==3)
		{
			LCD_Fill(128, 16*14, 144, 16*14.8, RED);  //风扇三档填充红色
			LCD_Fill(96, 16*14, 128, 16*14.8, GRAYBLUE);
		}
		LCD_Fill(100, 16*16, 130, 16*18, DARKBLUE); //风扇关闭按钮	    	    
		esp_Init();
		vTaskDelay(500);
	}
}





