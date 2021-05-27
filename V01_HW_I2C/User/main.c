
#include "Led.h"
#include "Lcd.h"
#include "Uart.h"
#include "I2C.h"
#include "stdio.h"
#include "Delay.h"
#include "FT6336U.h"
#include "Exit.h"
#include "I2C_HW.h"
#include "FT.h"
#include "Uart2.h"
#include "ESP8266_Sta.h"
#include "gizwits_product.h"
#include "timer.h"
#include "key.h"
#include "App.h"
#include "ADC.h"

u8 P;
u16 X,Y;
int8_t wifi_Sta;




//用户当前设备状态结构体
dataPoint_t currentDataPoint;

void Gizwits_Init(void)
{
    TIM3_Int_Init(9,7199);
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    gizwitsInit();
}

void userHandle(void)
{
    static u8 t=0;
    if(wifi_Sta)
    {
        t++;
        if(t==10)
        {
            t=0;
            gizwitsGetNTP();
        }
            Delay_Ms(600000);
        }else
            {if(t!=0)t=0;}
}





int main(void)
{	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LCD_init(); 
    menuInitial();
    KEY_init(); 
    Led_Init();
    ADC_init();
    Uart_Init(115200);
    I2C_init(); 
    FT6336U_init();
    
	Uart2_Init(9600);
    Gizwits_Init(); 
    printf("--------IOT-LED ----------\r\n");


   
    while(1)
    {
        Function_scan(); 
        P=FT_GetTouchPoints(0x02);
        X=FT_GetTouchPositionsY(0x03,0x04);
        Y=FT_GetTouchPositionsY(0x05,0x06);
        printf("Points=%d\r\nX=%d\r\nY=%d\r\n",P,X,Y);
       
    }
    

    
#if 0
    while(1)
    {
        userHandle();

        gizwitsHandle((dataPoint_t *)&currentDataPoint);  

        key = KEY_Scan(0);
        if(key==KEY1_PRES)//KEY1 
        {
            printf("WIFI进入AirLink连接\r\n");
            gizwitsSetMode(WIFI_AIRLINK_MODE); //Air-link 
        }
        if(key==WKUP_PRES)//KEY_UP 
        {
            printf("WIFI复位，请重新连接\r\n");
            gizwitsSetMode(WIFI_RESET_MODE);   //WIFI复位
        }   
//        
#if 0        
       Usart2_SendCmd("GET http://time.beijing-time.org/time.asp\r\n");
       Delay_Ms(5000000);
       OutPutLogo();
#endif        
    }
#endif    
    
}



void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
        {
            P=FT_GetTouchPoints(0x02);
            X=FT_GetTouchPositionsY(0x03,0x04);
            Y=FT_GetTouchPositionsY(0x05,0x06);
            printf("Points=%d\r\nX=%d\r\nY=%d\r\n",P,X,Y);
        }
    EXTI_ClearITPendingBit(EXTI_Line8);  
}

 
