


#ifndef __FT_H__
#define __FT_H__

#include "stm32f10x.h"

#define Cnt_I2C_Delay  0

void FT_Init(void);
u8 FT_GetTouchPoints(u8 Reg);
u16 FT_GetTouchPositionsX(u8 Addr_Xh,u8 Addr_Xl);
u16 FT_GetTouchPositionsY(u8 Addr_Yh,u8 Addr_Yl);

#endif
















