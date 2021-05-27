

#include "Exit.h"
#include "Uart.h"
#include "stm32f10x.h"




void Exit_Init(void)
{
    EXTI_InitTypeDef Exti_initStructure;
    NVIC_InitTypeDef NVIC_initStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);  

    
    Exti_initStructure.EXTI_Line=EXTI_Line8;
    Exti_initStructure.EXTI_Mode=EXTI_Mode_Interrupt;
    Exti_initStructure.EXTI_Trigger=EXTI_Trigger_Falling;
    Exti_initStructure.EXTI_LineCmd=ENABLE;
    EXTI_Init(&Exti_initStructure);


    NVIC_initStructure.NVIC_IRQChannel =EXTI9_5_IRQn; 
    NVIC_initStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_initStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_initStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_initStructure); 

}









