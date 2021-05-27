#include "FT.h"
#include "I2C_HW.h"
#include "Uart.h"
#include "Delay.h"

void FT_Init(void)
{					     
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	                       //RST 			
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(GPIOB, &GPIO_InitStructure);	


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	                       //INT			
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    GPIO_SetBits(GPIOB, GPIO_Pin_5);  
    Delay_Ms(50000);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    Delay_Ms(50000);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
}


u8 I2C_HW_BufferRead(u8 ReadAddr)
{  

    u8 Dat;
    I2C_GenerateSTART(I2C1, ENABLE);
    Delay_Ms(Cnt_I2C_Delay); 
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));   //Start
    

//    printf("***1***\r\n");

    I2C_Send7bitAddress(I2C1, 0x70, I2C_Direction_Transmitter);
    Delay_Ms(Cnt_I2C_Delay); 
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //Send HW address
    
//    printf("***2***\r\n");
    
    I2C_Cmd(I2C1, ENABLE);
    I2C_SendData(I2C1, ReadAddr); 
    Delay_Ms(Cnt_I2C_Delay);     //Data Address                
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
//    printf("***3***\r\n");
    
    I2C_GenerateSTART(I2C1, ENABLE);
    Delay_Ms(Cnt_I2C_Delay); 
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));   // Repeat Start 
//    printf("***4***\r\n");
    
    I2C_Send7bitAddress(I2C1, 0x71, I2C_Direction_Receiver);
    Delay_Ms(Cnt_I2C_Delay); 
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); 
    
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE); 
    while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)==0);  
    
    Delay_Ms(Cnt_I2C_Delay);    
    Dat=I2C_ReceiveData(I2C1);
    
    return Dat ;
  }


  
  

u8 FT_GetTouchPoints(u8 Reg)
{
    u8 TouchPoints;
    TouchPoints=I2C_HW_BufferRead(Reg)&0x0F;  
    return TouchPoints;
}

u16 FT_GetTouchPositionsX(u8 Addr_Xh,u8 Addr_Xl)
{
    u8 TouchPositionsX_H;
    u8 TouchPositionsX_L;
    u16 TouchPositionX;
    TouchPositionsX_H=I2C_HW_BufferRead(Addr_Xh)&0xF;
    TouchPositionsX_L=I2C_HW_BufferRead(Addr_Xl);
    TouchPositionX=((TouchPositionsX_H<<8)|TouchPositionsX_L)&0xFFF;
    return TouchPositionX;
}

u16 FT_GetTouchPositionsY(u8 Addr_Yh,u8 Addr_Yl)
{
    u8 TouchPositionsY_H;
    u8 TouchPositionsY_L;
    u16 TouchPositionY;
    TouchPositionsY_H=I2C_HW_BufferRead(Addr_Yh)&0xF;
    TouchPositionsY_L=I2C_HW_BufferRead(Addr_Yl);
    TouchPositionY=((TouchPositionsY_H<<8)|TouchPositionsY_L)&0xFFF;
    return TouchPositionY;
}










