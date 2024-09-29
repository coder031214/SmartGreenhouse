#include "gy30.h"
#include "delay.h"
#include "myiic.h"
  
void Send_BH_DATA(u8 command)  
{  
  do{  
    IIC_Start();                   //iic开始
    IIC_Send_Byte(BHAddWrite);     //写地址  
    }
	while(IIC_Wait_Ack());           //等待响应 
    IIC_Send_Byte(command);        //发送命令  
    IIC_Wait_Ack();                //等待响应 
    IIC_Stop();                    //iic停止  
}   

//读光照强度
u16 Read_BH_DATA(void)  
{  
    u16 buf;  
    IIC_Start();                       //iic开始  
    IIC_Send_Byte(BHAddRead);          //发送读地址
    IIC_Wait_Ack();                    //等待响应  
    buf=IIC_Read_Byte(1);              //读取数据  
    buf=buf<<8;                        //读取并保存高八位数据
    buf+=0x00ff&IIC_Read_Byte(0);      //读取并保存第八位数据
    IIC_Stop();                        //发送停止信号
    return buf;   
}  

//光照强度初始化
void GY30_Init(void)
{
	IIC_Init();		//IIC初始化
	Send_BH_DATA(BHPowOn);    //发送启动信号
	Send_BH_DATA(BHReset);    //清除寄存器  
  Send_BH_DATA(BHModeH1);   //设置为模式2
  delay_ms(180);            //最高延时180ms
}
