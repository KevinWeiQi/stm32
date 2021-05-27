#include "FT6336U.h"
#include "I2C.h"
#include "Uart.h"
	
#include "Delay.h"




void FT6336U_init(void)
{					     
        GPIO_InitTypeDef  GPIO_InitStructure;
	
        Ft6336u_RST_RCC_AHBPeriphClockCmd(Ft6336u_RST_RCC_AHBPeriph, ENABLE);    

        GPIO_InitStructure.GPIO_Pin = Ft6336u_RST_Pin;	     
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
        GPIO_Init(Ft6336u_RST_Port,&GPIO_InitStructure);	
        GPIO_SetBits(Ft6336u_RST_Port, Ft6336u_RST_Pin);  
        Delay_Ms(50000);
        GPIO_ResetBits(Ft6336u_RST_Port, Ft6336u_RST_Pin);
        Delay_Ms(50000);
        GPIO_SetBits(Ft6336u_RST_Port, Ft6336u_RST_Pin);
    
        GPIO_InitStructure.GPIO_Pin = Ft6336u_INT_Pin;	     
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(Ft6336u_INT_Port,&GPIO_InitStructure);	
        GPIO_ResetBits(Ft6336u_INT_Port, Ft6336u_INT_Pin);         
		      			  
}


u8 FT6336U_readOneByte(u8 Reg)
{
    u8 dat;
    I2C_Start();

    I2C_Write(FT6336U_write); 
    I2C_Write(Reg);   
 
    I2C_Start();  
    I2C_Write(FT6336U_read); 

    dat=I2C_ReadNak();         
    I2C_Stop();
    return dat;
}

u8 FT6336U_getTouchPoints(u8 Reg)
{
    u8 touchPoints;
    touchPoints=FT6336U_readOneByte(Reg)&0x0F;  
    return touchPoints;
}

u16 FT6336U_getTouchPositionsX(u8 Addr_Xh,u8 Addr_Xl)
{
    u8 touchPositionsX_H;
    u8 touchPositionsX_L;
    u16 touchPositionX;
    touchPositionsX_H=FT6336U_readOneByte(Addr_Xh)&0xF;
    touchPositionsX_L=FT6336U_readOneByte(Addr_Xl);
    touchPositionX=((touchPositionsX_H<<8)|touchPositionsX_L)&0xFFF;
    return touchPositionX;
}

u16 FT6336U_getTouchPositionsY(u8 Addr_Yh,u8 Addr_Yl)
{
    u8 touchPositionsY_H;
    u8 touchPositionsY_L;
    u16 touchPositionY;
    touchPositionsY_H=FT6336U_readOneByte(Addr_Yh)&0xF;
    touchPositionsY_L=FT6336U_readOneByte(Addr_Yl);
    touchPositionY=((touchPositionsY_H<<8)|touchPositionsY_L)&0xFFF;
    return touchPositionY;
}














