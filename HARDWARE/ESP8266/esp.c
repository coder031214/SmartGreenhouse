#include "stm32f10x.h"                  // Device header
#include <stdbool.h>
#include <stdio.h>
#include "delay.h"
#include "usart2.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stm32f10x_rcc.h"
#include "esp.h"
#include "usart.h"
#include "beep.h"
#include "led.h"




#include <string.h>	//内存操作相关函数库
#include <stdio.h>
#include <stdbool.h>
extern int Temperature;
extern int PumpSwitch;
extern int LightPercent;
extern int Shidu;
extern char RECS[250];
uint8_t WIFI[] ="X";				//WIFI名称
uint8_t WIFIASSWORD[]="88888888";		//WIFI密码

//char* ClintID="k0vgkvM8gZu.wenshi|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710329247606|";
//char* username="wenshi&k0vgkvM8gZu";
//char* passwd="69c0316c2bb67a9391f85b8a9aa8790f1cdc96e80c677c68e63d83f517288098";
//char* Url="iot-06z00g9iwaysy4z.mqtt.iothub.aliyuncs.com";
//char* pubtopic="/sys/k0vgkvM8gZu/wenshi/thing/event/property/post";
//char* subtopic="/k0vgkvM8gZu/wenshi/user/get";

//AT+MQTTUSERCFG=0,1,"k0vgkvM8gZu.wenshi|securemode=2\,signmethod=hmacsha256\,timestamp=1710329247606|","wenshi&k0vgkvM8gZu","69c0316c2bb67a9391f85b8a9aa8790f1cdc96e80c677c68e63d83f517288098",0,0,""
char* ClintID="k0ow793yb7M.GreenHouse|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710657490831|";
char* username="GreenHouse&k0ow793yb7M";
char* passwd="9cde987aa6d7521e57795afa0253cafbe4da83f5d09a9ac2514df82b611a1f15";
char* Url="iot-06z00dbbdfr9ud9.mqtt.iothub.aliyuncs.com";
char* pubtopic="/sys/k0ow793yb7M/GreenHouse/thing/event/property/post";
char* subtopic="/k0ow793yb7M/GreenHouse/user/get";


uint8_t wiflpw[128]="AT+CWJAP=\"1\"\\,\"88888888\"";
uint8_t usercfg[128];
uint8_t conn[256];
uint8_t sub1[256];
uint8_t sub2[256];
uint8_t pub[300];
int NetWorkStatu=0;
char* wifl="0100010";
//const unsigned char static gImage_16[153600];


 u8 air_temprature;	//空气温度
 u8 air_humidity;	//空气湿度
 u32 CO2_level;	//二氧化碳浓度
 u32 TVOC_levle;	//甲醛浓度
 int soil_temprature; //土壤温度
 float soil_humidity;	//土壤湿度
 int soil_PH_level; //土壤PH值
 int light_intensity; //光照强度
 int fan_speed;	//风扇转速


bool substringMatch(const char *text, const char *pattern) {
    int i, j;
    int textLen = strlen(text);
    int patternLen = strlen(pattern);
    
    for (i = 0; i <= textLen - patternLen; i++) {
        for (j = 0; j < patternLen; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        
        if (j == patternLen) {
            return true;  // 子串匹配成功
        }
    }
    
    return false;  // 子串匹配失败
}

char esp_Init(void)
{
	int flag=0;
	
	//SendAtCmd((uint8_t *)"ATE0\r\n",strlen("ATE0\r\n")); 
	//memset(RECS,0,sizeof(RECS));
	SendAtCmd((uint8_t *)"AT+RST\r\n",strlen("AT+RST\r\n")); 
	//printf("AT+RST send\r\n");
	
	//delay_ms(4000);
	//while(!substringMatch(RECS,"OK"));
	//memset(RECS,0,sizeof(RECS));
	//delay_ms(2000);
	
	
//	delay_ms(2000);

//	
	//memset(RECS,0,sizeof(RECS));
	//delay_ms(2000);

	
	//memset(RECS,0,sizeof(RECS));
	SendAtCmd((uint8_t *)("AT+CWMODE=1\r\n"),strlen("AT+CWMODE=1\r\n")); 
	//printf("AT+CWMODE=1 send\r\n");	
	//memset(RECS,0,sizeof(RECS));
	
//	sprintf(WIFI,"1");
//	sprintf(WIFIASSWORD,"88888888");
//	
//	sprintf(wiflpw,"AT+CWJAP=\"1\"\,\"88888888\"",WIFI,WIFIASSWORD);
	SendAtCmd((uint8_t *)("AT+CWJAP=\"1\"\,\"88888888\""),strlen("AT+CWJAP=\"1\"\\,\"88888888\"")); 		
	delay_ms(1000);
	while(!flag)
		{
			int i;
			for( i=0;i<10;i++)
			{			
				if(substringMatch(RECS,"WIFI GOT IP")==1){printf("wifl connect succeed\r\n");flag=1;break;};
				if(substringMatch(RECS,"CWJAP:3")==1){printf("wifl connect failed\r\n");flag=2;break;}
				//memset(RECS,0,sizeof(RECS));
				delay_ms(1000);
			}
		}
	
	
	if(flag==1)
	{
		SendAtCmd((uint8_t*)"AT+CWAUTOCONN=0\r\n",strlen("AT+CWAUTOCONN\r\n")); 
		while(!strcmp(RECS,"OK"));
		memset(RECS,0,sizeof(RECS));
		delay_ms(2000);	
		
//		sprintf(ClintID,"k0ow793yb7M.GreenHouse|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710657490831|");
//		sprintf(username,"GreenHouse&k0ow793yb7M");
//		sprintf(passwd,"9cde987aa6d7521e57795afa0253cafbe4da83f5d09a9ac2514df82b611a1f15");
		
		//sprintf((char *)usercfg,"AT+MQTTUSERCFG=0,1,\"k0ow793yb7M.GreenHouse|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710657490831|\",\"GreenHouse&k0ow793yb7M\",\"9cde987aa6d7521e57795afa0253cafbe4da83f5d09a9ac2514df82b611a1f15\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
		
		SendAtCmd((uint8_t*)"AT+MQTTUSERCFG=0,1,\"k0ow793yb7M.GreenHouse|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710657490831|\",\"GreenHouse&k0ow793yb7M\",\"9cde987aa6d7521e57795afa0253cafbe4da83f5d09a9ac2514df82b611a1f15\",0,0,\"\"\r\n",strlen("AT+MQTTUSERCFG=0,1,\"k0ow793yb7M.GreenHouse|securemode=2\\,signmethod=hmacsha256\\,timestamp=1710657490831|\",\"GreenHouse&k0ow793yb7M\",\"9cde987aa6d7521e57795afa0253cafbe4da83f5d09a9ac2514df82b611a1f15\",0,0,\"\"\r\n")); 
		delay_ms(2000);
		while(!strcmp(RECS,"OK"));

		memset(RECS,0,sizeof(RECS));		
		//sprintf((char *)conn,"AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
		SendAtCmd((uint8_t*)"AT+MQTTCONN=0,\"iot-06z00dbbdfr9ud9.mqtt.iothub.aliyuncs.com\",1883,1\r\n",strlen("AT+MQTTCONN=0,\"iot-06z00dbbdfr9ud9.mqtt.iothub.aliyuncs.com\",1883,1\r\n")); 
		delay_ms(2000);	
		while(!strcmp(RECS,"OK"));			
		memset(RECS,0,sizeof(RECS));
		
	//	sprintf((char *)sub1,"AT+MQTTSUB=0,\"/k0ow793yb7M/GreenHouse/user/get\",1\r\n"); //订阅消息（已修改）
		SendAtCmd((uint8_t*)"AT+MQTTSUB=0,\"/k0ow793yb7M/GreenHouse/user/get\",1\r\n",strlen("AT+MQTTSUB=0,\"/k0ow793yb7M/GreenHouse/user/get\",1\r\n")); 
		delay_ms(2000);
		while(!strcmp(RECS,"OK"));
		memset(RECS,0,sizeof(RECS));
		
		//sprintf((char *)sub2,"AT+MQTTSUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",1\r\n"); //订阅消息（已修改）
		SendAtCmd((uint8_t*)"AT+MQTTSUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",1\r\n",strlen("AT+MQTTSUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",1\r\n")); 
		delay_ms(2000);	
			
		memset(RECS,0,sizeof(RECS));
		printf("service connect succeed\r\n");
		NetWorkStatu=1;
		return 0;
	
	}
	printf("service connect failed\r\n");
	if(flag==2)
	{
		printf("reconnect wifl and server\r\n");
		esp_Init();
	}
	//return 0;
}
//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
//char Esp_PUB(void)
//{
//	memset(pub,0,sizeof(pub));
//	sprintf((char *)pub,"AT+MQTTPUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",\"{params:{\\\"air_temprature\\\":%d\\,\\\"air_humidity\\\":%d\\,\\\"CO2_level\\\":%d\\,\\\"TVOC_levle\\\":%d}}\",0,0\r\n",air_temprature,air_humidity,CO2_level,TVOC_levle);
//	SendAtCmd((uint8_t*)pub,strlen(pub)); 
//	printf("----PUB---1---OK\r\n");
//	delay_ms(4000);	
//	
//	memset(pub,0,sizeof(pub));
//	sprintf((char *)pub,"AT+MQTTPUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",\"{params:{\\\"soil_temprature\\\":%d\\,\\\"soil_humidity\\\":%f}}\",0,0\r\n",soil_temprature,soil_humidity);
//    SendAtCmd((uint8_t*)pub,strlen(pub));  
//	delay_ms(4000);	
//	
//	memset(pub,0,sizeof(pub));
//	printf("----PUB----2---OK\r\n");
//	sprintf((char *)pub,"AT+MQTTPUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",\"{params:{\\\"soil_PH_level\\\":%d\\,\\\"light_intensity\\\":%d\\,\\\"fan_speed\\\":%d}}\",0,0\r\n",soil_PH_level,light_intensity,fan_speed);
//    SendAtCmd((uint8_t*)pub,strlen(pub));   	
////	if(strcmp(RECS,"ERROR")==0)          
////		return 1;
//	
//	printf("----PUB----3---OK\r\n");
//	return 0;
//}

char Esp_PUB(void)
{
	//memset(pub,0,sizeof(pub));
	sprintf((char *)pub,"AT+MQTTPUB=0,\"/sys/k0ow793yb7M/GreenHouse/thing/event/property/post\",\"{params:{\\\"air_temp\\\":%d\\,\\\"air_humi\\\":%d\\,\\\"CO2\\\":%d\\,\\\"TVOC\\\":%d\\,\\\"soil_temp\\\":%d\\,\\\"soil_humi\\\":%f\\,\\\"PH\\\":%d\\,\\\"light\\\":%d\\,\\\"fan\\\":%d}}\",0,0\r\n",air_temprature,air_humidity,CO2_level,TVOC_levle,soil_temprature,soil_humidity,soil_PH_level,light_intensity,fan_speed);
	
	printf("----PUB----3---%s\r\n",pub);
	//sprintf((char *)pub,"AT+MQTTPUB=0,\"/sys/k0vgkvM8gZu/wenshi/thing/event/property/post\",\"{params:{\\\"air_temprature\\\":%d\\,\\\"air_humidity\\\":%d}}\",0,0\r\n",air_temprature,air_humidity);
	printf("----PUB----4---%d\r\n",strlen(pub));	
	SendAtCmd((uint8_t*)pub,strlen(pub));
	
	
	//usart2_recve_ok_SendStrlen((uint8_t*)pub,strlen(pub));
	delay_ms(4000);		
	printf("----PUB----3---OK\r\n");
	return 0;
}




int analy(char * memu)	//解析云端发来数据，参数为接收的元素，返回的为接收的值
{

	if(substringMatch((const char *)RECS, (const char *)memu)==true)//开锁/关锁请求
	{	
		printf("The memu key was found .\r\n");
		char * valuePtr = strstr((char *)RECS, "value");
		if (valuePtr!=NULL) 
		{
			printf("valuePtr is-- %s\r\n", valuePtr);
			// 跳过"value":这部分，到达数字部分
			valuePtr += strlen("value\":");
			// 读取value值
			int value = atoi(valuePtr);
			printf("The %s is: %d\r\n",memu, value);
			return value;
		}
	else{		
			printf("The memu key was not found in the string.\r\n");
			return 0;
		}
	}
	return 0;
}

















