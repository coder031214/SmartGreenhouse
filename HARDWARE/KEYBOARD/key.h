#ifndef __KEY_H_
#define __KEY_H_

#define in_1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)
#define in_2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)
#define in_3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)
#define in_4 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)

void key_board_exti_init(void);
void key_1_init(void);
void key_2_init(void);


u8 Get_keyValue(void);

#endif
