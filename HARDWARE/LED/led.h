#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED0 PBout(5) //LED0
#define LED1 PEout(5) //LED1

#define LED_YELLOW PEout(0) //黄灯
#define LED_GREEN PEout(1) //绿灯
#define LED_RED PEout(2) //红灯

enum led_color
{
	yellow,
	green,
	red,
	close_all
};


void led_init(void);
void led_change(enum led_color color); //不同颜色的小灯翻转


#endif
