#ifndef __PH_H
#define __PH_H	

void PH_adc_gpio_init(void);	//gpio��ʼ��
void PH_adc_init(void);	//ADC1��ʼ��
int PH_Get_Adc(int ch);	
int PH_Get_Adc_Average(int channel,int count);
void PH_Init(void); //PH��ʼ��
float GetPH(void); //��ȡPHֵ


#endif 
