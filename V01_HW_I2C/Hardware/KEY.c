#include "key.h"
#include "lcd.h"
#include "delay.h"
#include "Uart.h"





void KEY_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
} 

u8 KEY0_scan(void)
{
    u8 status=0;
    if(0==KEY0)
    {
       Delay_Ms(500000);
       if(0==KEY0)
       {
           status=1;
       }     
    } 
    return status;    
}

u8 KEY1_scan(void)
{
    u8 status=0;
    if(0==KEY1)
    {
       Delay_Ms(500000);
       if(0==KEY1)
       {
           status=1;
       }     
    }
    return status;
}


u8 KEYUP_scan(void)
{
    u8 status=0;
    if(1==KEYUP)
    {
       Delay_Ms(500000);
       if(1==KEYUP)
       {
            status=1;
       }     
    }  
    return status;    
}







