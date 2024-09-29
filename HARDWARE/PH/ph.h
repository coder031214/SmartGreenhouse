#ifndef __PH_H
#define __PH_H	

void PH_adc_gpio_init(void);	//gpio初始化
void PH_adc_init(void);	//ADC1初始化
int PH_Get_Adc(int ch);	
int PH_Get_Adc_Average(int channel,int count);
void PH_Init(void); //PH初始化
float GetPH(void); //获取PH值


#endif 
