#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"

#define BEEP PBout(8)	// BEEP,�������ӿ�

void beep_init(void);	//��ʼ��
void beep_play(int count); //��������Ӧ����

#endif
