#ifndef __SOILHUMI_H
#define __SOILHUMI_H 

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //��ȡGPIOA��P0�ڵ�ƽ��0/1��
 
void Gpio_Init(void);         //��ʱ��ʼ������
int Gpio_read(void);        //��ȡA0��
void Adc_Init(void);
int Get_Adc(int ch);
int Get_Adc_Average(int channel,int count);
void SoilHumi_Init(void); 
float Get_SoilHumi(void);
 
#endif
