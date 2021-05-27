#ifndef __KEY_H_
#define __KEY_H_	 

#include "stm32f10x.h"
 

#define KEY0    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)  //��ȡ����0
#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) //��ȡ����1
#define KEYUP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //��ȡ����2 
 

void KEY_init(void);
u8 KEY0_scan(void);
u8 KEY1_scan(void);
u8 KEYUP_scan(void);
#endif
