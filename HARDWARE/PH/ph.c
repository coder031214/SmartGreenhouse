#include "ph.h"
#include "delay.h"

void PH_adc_gpio_init(void) //GPIO初始化
{
    GPIO_InitTypeDef t_gpio;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能 GPIOA 时钟
    t_gpio.GPIO_Pin = GPIO_Pin_1;
    t_gpio.GPIO_Mode = GPIO_Mode_AIN; //模拟输入模式
    GPIO_Init(GPIOA, &t_gpio);         //初始化GPIOA
}

void PH_adc_init(void) //ADC2初始化
{
    ADC_InitTypeDef t_adc;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //使能ADC2时钟

    t_adc.ADC_Mode = ADC_Mode_Independent;                 //独立模式：ADC2与ADC1独立
    t_adc.ADC_ScanConvMode = DISABLE;                      //禁用通道扫描
    t_adc.ADC_ContinuousConvMode = DISABLE;                //禁用连续转换
    t_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不使用外部触发
    t_adc.ADC_DataAlign = ADC_DataAlign_Right;             //数据位右对齐
    t_adc.ADC_NbrOfChannel = 1;                            //转换通道数为1
    ADC_Init(ADC2, &t_adc);                                //初始化ADC2

    RCC_ADCCLKConfig(RCC_PCLK2_Div8); //配置ADC时钟为PCLK2的8分频

    ADC_Cmd(ADC2, ENABLE); //使能ADC2

    ADC_ResetCalibration(ADC2);
    while (ADC_GetResetCalibrationStatus(ADC2))
        ;
    ADC_StartCalibration(ADC2); //校准
    while (ADC_GetCalibrationStatus(ADC2))
        ;
}

int PH_Get_Adc(int ch)
{
    ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5); //ADC2,ADC通道,采样时间为239.5周期
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);                           //使能指定的ADC2的软件转换启动功能
    while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))
        ; //等待转换结束
    return ADC_GetConversionValue(ADC2);                          //返回最近一次ADC2规则组的转换结果
}

int PH_Get_Adc_Average(int channel, int count)
{
    int sum_val = 0;
    char t;

    for (t = 0; t < count; t++) //循环读取times次
    {
        sum_val += PH_Get_Adc(channel); //计算总值
        delay_ms(5);                    //延时
    }
    return sum_val / count; //返回平均值
}

void PH_Init()
{
    PH_adc_gpio_init(); //PH GPIO初始化
    PH_adc_init();      //PH ADC2初始化
}

float GetPH(void) //返回得到PH值，使用PA1通道采集
{
    u16 adcx;
    float ph;
    float temp;
    adcx = PH_Get_Adc_Average(ADC_Channel_2, 10);
    temp = (float)adcx * (3.3 / 4096);
    ph = -4.7541 * temp + 16.154;
    return ph;
}
