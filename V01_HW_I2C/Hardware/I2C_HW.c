
#include "I2C_HW.h"
#include "stm32f10x.h"

void I2C_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //enable GPIO Clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);    //enable I2C1 Clock

    GPIO_InitStructure.GPIO_Pin= GPIO_Pin_6|GPIO_Pin_7;         //config SDA,SCL
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	
	
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void I2C_Mode_Config(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    I2C_DeInit(I2C1);    
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 =0X0A ; 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_Init(I2C1, &I2C_InitStructure);
    I2C_Cmd(I2C1, ENABLE);   
}


void I2C_HW_Init(void)
{
    I2C_GPIO_Config();
    I2C_Mode_Config();
}






