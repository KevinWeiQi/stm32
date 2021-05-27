


#ifndef __FT6336U_H__
#define __FT6336U_H__

#include "stm32f10x.h"


//#define Ft6336u_Rst_Pin GPIO_Pin_8    //PA8
//#define Ft6336u_Int_Pin GPIO_Pin_11   //PA11


#define      Ft6336u_RST_RCC_AHBPeriphClockCmd      RCC_APB2PeriphClockCmd
#define      Ft6336u_RST_RCC_AHBPeriph              RCC_APB2Periph_GPIOA
#define      Ft6336u_RST_Port                       GPIOA
#define      Ft6336u_RST_Pin                        GPIO_Pin_4

#define      Ft6336u_INT_RCC_AHBPeriphClockCmd      RCC_APB2PeriphClockCmd  
#define      Ft6336u_INT_RCC_AHBPeriph              RCC_APB2Periph_GPIOC
#define      Ft6336u_INT_Port                       GPIOC
#define      Ft6336u_INT_Pin                        GPIO_Pin_4




#define FT6336U_write 0x70//0x70
#define FT6336U_read  0x71




void FT6336U_init(void);
u8 FT6336U_readOneByte(u8 Reg);
u8 FT6336U_getTouchPoints(u8 Reg);
u16 FT6336U_getTouchPositionsX(u8 Addr_Xh,u8 Addr_Xl);
u16 FT6336U_getTouchPositionsY(u8 Addr_Yh,u8 Addr_Yl);
void KevinTest(void);





#endif
















