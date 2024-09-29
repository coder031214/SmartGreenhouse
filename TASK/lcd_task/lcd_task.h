#ifndef __LCD_TASK_H
#define __LCD_TASK_H
#include "sys.h"
#include "getsensor_task.h"

void lcd_draw_start(void);
void lcd_init(void);
void lcd_task(Sensor_Data_t *Sensor_Data);



#endif
