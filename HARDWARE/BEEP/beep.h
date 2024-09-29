#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"

#define BEEP PBout(8)	// BEEP,蜂鸣器接口

void beep_init(void);	//初始化
void beep_play(int count); //蜂鸣器响应次数

#endif
