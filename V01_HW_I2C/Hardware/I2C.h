


#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f10x.h"



#define      FT_I2C_SDA_RCC_AHBPeriphClockCmd      RCC_APB2PeriphClockCmd
#define      FT_I2C_SDA_RCC_AHBPeriph                 RCC_APB2Periph_GPIOA
#define      FT_I2C_SDA_Port                              GPIOA
#define      FT_I2C_SDA_Pin                               GPIO_Pin_7

#define      FT_I2C_SCL_RCC_AHBPeriphClockCmd      RCC_APB2PeriphClockCmd  
#define      FT_I2C_SCL_RCC_AHBPeriph                  RCC_APB2Periph_GPIOA 
#define      FT_I2C_SCL_Port                               GPIOA
#define      FT_I2C_SCL_Pin                                GPIO_Pin_5





#define delay_I2cBus 20

void I2C_init(void);
void I2C_Start(void);
void I2C_Stop(void);
u8 I2C_Write(u8 dat);
u8 I2C_ReadAck(void);
u8 I2C_ReadNak(void);



#endif
















