

#ifndef __UART2_H__
#define __UART2_H__

#include "stm32f10x.h"
#include "stdio.h"


extern u16 Index_Recive;
extern u8 Flag_RxFinish;
extern char Buffer_RX[1024];


void Uart2_Init(u32 bound);
void Usart2_SendCmd(char *str);
#endif












