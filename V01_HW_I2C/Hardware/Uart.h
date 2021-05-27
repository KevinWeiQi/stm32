

#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include "stdio.h"

extern char Buffer_RxData[200];
extern u8 Flag_Rx;
extern char RxData;
extern u8 Index;
void Uart_Init(u32 bound);

void Usart1_SendCmd(char *str);
void OutPutLogo(void);
void SendString(u8 dat);
#endif












