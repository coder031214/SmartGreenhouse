#include "gy30.h"
#include "delay.h"
#include "myiic.h"
  
void Send_BH_DATA(u8 command)  
{  
  do{  
    IIC_Start();                   //iic��ʼ
    IIC_Send_Byte(BHAddWrite);     //д��ַ  
    }
	while(IIC_Wait_Ack());           //�ȴ���Ӧ 
    IIC_Send_Byte(command);        //��������  
    IIC_Wait_Ack();                //�ȴ���Ӧ 
    IIC_Stop();                    //iicֹͣ  
}   

//������ǿ��
u16 Read_BH_DATA(void)  
{  
    u16 buf;  
    IIC_Start();                       //iic��ʼ  
    IIC_Send_Byte(BHAddRead);          //���Ͷ���ַ
    IIC_Wait_Ack();                    //�ȴ���Ӧ  
    buf=IIC_Read_Byte(1);              //��ȡ����  
    buf=buf<<8;                        //��ȡ������߰�λ����
    buf+=0x00ff&IIC_Read_Byte(0);      //��ȡ������ڰ�λ����
    IIC_Stop();                        //����ֹͣ�ź�
    return buf;   
}  

//����ǿ�ȳ�ʼ��
void GY30_Init(void)
{
	IIC_Init();		//IIC��ʼ��
	Send_BH_DATA(BHPowOn);    //���������ź�
	Send_BH_DATA(BHReset);    //����Ĵ���  
  Send_BH_DATA(BHModeH1);   //����Ϊģʽ2
  delay_ms(180);            //�����ʱ180ms
}
