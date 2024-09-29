#include "ph.h"
#include "delay.h"

void PH_adc_gpio_init(void) //GPIO��ʼ��
{
    GPIO_InitTypeDef t_gpio;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ�� GPIOA ʱ��
    t_gpio.GPIO_Pin = GPIO_Pin_1;
    t_gpio.GPIO_Mode = GPIO_Mode_AIN; //ģ������ģʽ
    GPIO_Init(GPIOA, &t_gpio);         //��ʼ��GPIOA
}

void PH_adc_init(void) //ADC2��ʼ��
{
    ADC_InitTypeDef t_adc;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC2ʱ��

    t_adc.ADC_Mode = ADC_Mode_Independent;                 //����ģʽ��ADC2��ADC1����
    t_adc.ADC_ScanConvMode = DISABLE;                      //����ͨ��ɨ��
    t_adc.ADC_ContinuousConvMode = DISABLE;                //��������ת��
    t_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //��ʹ���ⲿ����
    t_adc.ADC_DataAlign = ADC_DataAlign_Right;             //����λ�Ҷ���
    t_adc.ADC_NbrOfChannel = 1;                            //ת��ͨ����Ϊ1
    ADC_Init(ADC2, &t_adc);                                //��ʼ��ADC2

    RCC_ADCCLKConfig(RCC_PCLK2_Div8); //����ADCʱ��ΪPCLK2��8��Ƶ

    ADC_Cmd(ADC2, ENABLE); //ʹ��ADC2

    ADC_ResetCalibration(ADC2);
    while (ADC_GetResetCalibrationStatus(ADC2))
        ;
    ADC_StartCalibration(ADC2); //У׼
    while (ADC_GetCalibrationStatus(ADC2))
        ;
}

int PH_Get_Adc(int ch)
{
    ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5); //ADC2,ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);                           //ʹ��ָ����ADC2�����ת����������
    while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))
        ; //�ȴ�ת������
    return ADC_GetConversionValue(ADC2);                          //�������һ��ADC2�������ת�����
}

int PH_Get_Adc_Average(int channel, int count)
{
    int sum_val = 0;
    char t;

    for (t = 0; t < count; t++) //ѭ����ȡtimes��
    {
        sum_val += PH_Get_Adc(channel); //������ֵ
        delay_ms(5);                    //��ʱ
    }
    return sum_val / count; //����ƽ��ֵ
}

void PH_Init()
{
    PH_adc_gpio_init(); //PH GPIO��ʼ��
    PH_adc_init();      //PH ADC2��ʼ��
}

float GetPH(void) //���صõ�PHֵ��ʹ��PA1ͨ���ɼ�
{
    u16 adcx;
    float ph;
    float temp;
    adcx = PH_Get_Adc_Average(ADC_Channel_2, 10);
    temp = (float)adcx * (3.3 / 4096);
    ph = -4.7541 * temp + 16.154;
    return ph;
}
