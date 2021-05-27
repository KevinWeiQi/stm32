

#include "Led.h"	
#include "Delay.h"	


void Led_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //Ê¹ÄÜPA,PD¶Ë¿ÚÊ±ÖÓ

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 ¶Ë¿ÚÅäÖÃ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO¿ÚËÙ¶ÈÎª50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //¸ù¾ÝÉè¶¨²ÎÊý³õÊ¼»¯GPIOA.8
	GPIO_SetBits(GPIOA,GPIO_Pin_8);						     //PA.8 Êä³ö¸ß

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 ¶Ë¿ÚÅäÖÃ, ÍÆÍìÊä³ö
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //ÍÆÍìÊä³ö £¬IO¿ÚËÙ¶ÈÎª50MHz
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 Êä³ö¸ß 	 
}


void Led_module(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
    Delay_Ms(1000000);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
    GPIO_ResetBits(GPIOD,GPIO_Pin_2);
    Delay_Ms(1000000);    
}
void Led_moduleClear(void)
{
   
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);

}







