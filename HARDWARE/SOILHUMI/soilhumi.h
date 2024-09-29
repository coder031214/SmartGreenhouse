#ifndef __SOILHUMI_H
#define __SOILHUMI_H 

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //读取GPIOA的P0口电平（0/1）
 
void Gpio_Init(void);         //延时初始化函数
int Gpio_read(void);        //读取A0口
void Adc_Init(void);
int Get_Adc(int ch);
int Get_Adc_Average(int channel,int count);
void SoilHumi_Init(void); 
float Get_SoilHumi(void);
 
#endif
