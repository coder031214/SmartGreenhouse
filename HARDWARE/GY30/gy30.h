#ifndef __GY30_H_
#define __GY30_H_
#include "sys.h"

//����
#define BHAddWrite     0x46      //д��ַ
#define BHAddRead      0x47      //����ַ
#define BHPowDown      0x00      //�ر�ģ��
#define BHPowOn        0x01      //��ģ��ȴ�ָ�� 
#define BHReset        0x07      //�������ݼĴ�������BHpowOnģʽ����Ч
#define BHModeH1       0x10      //�߷ֱ��� ģʽ1 ��λ 11X ����ʱ�� 120ms 
#define BHModeH2       0x11      //�߷ֱ��� ģʽ2 ��λ 11X ����ʱ�� 120ms 
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms  
#define BHSigModeH     0x20      //һ�β����߷ֱ���ģʽ1��Ȼ��ת��powerdownģʽ
#define BHSigModeH2    0x21      //ͬ������
#define BHSigModeL     0x23      //ͬ������  

void Send_BH_DATA(unsigned char command);
u16 Read_BH_DATA(void);
void GY30_Init(void);


#endif

