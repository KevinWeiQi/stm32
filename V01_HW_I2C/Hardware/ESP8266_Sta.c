
#include "ESP8266_Sta.h"
#include "stdio.h"		
#include "Uart2.h"
#include "Delay.h"
#include "String.h"
#include "Uart.h"


#define GUEST  1

char *CWMODE="AT+CWMODE=1\r\n";
char *RST="AT+RST\r\n";
char *CWJAP="AT+CWJAP=";

#if GUEST
    char *NAME="Network_88";
    char *PASSWORD="20160213";
#else 
    char *NAME="Kevin";
    char *PASSWORD="20140201";
#endif


char *CIPMUX="AT+CIPMUX=0\r\n";
char *CIPSTART="AT+CIPSTART=";
char *TCP="TCP";
char *SERVER="time.beijing-time.org";
char *PORT="80\r\n"; 
char *CIPMODE="AT+CIPMODE=1\r\n";
char *CIPSEND="AT+CIPSEND\r\n";

char *STATUS="OK";


char Buffer[100];


u8* ESP8266_CheckAck(char *Str)
{
    char *pIndex=0;
    if(1==Flag_RxFinish)
    {
        pIndex=strstr((const char*)Buffer_RX,(const char*)Str);
    }
    return (u8*)pIndex;
}

#if 1

void ESP8266_WaitAck(void)
{
    do{
            Usart2_SendCmd(Buffer); 
            Usart1_SendCmd(Buffer); 
            Delay_Ms(60000000);
            printf("ESP8266_WaitAck\r\n");
            GPIO_ResetBits(GPIOA,GPIO_Pin_8);
        }
    while(!ESP8266_CheckAck(STATUS));
    GPIO_SetBits(GPIOA,GPIO_Pin_8);

}

#endif







void ESP8266_getWeather(void)
{
#if 1 
    Usart2_SendCmd(CWMODE);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
 
    Usart2_SendCmd(RST);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
    sprintf(Buffer,"%s\"%s\",\"%s\"\r\n",CWJAP,NAME,PASSWORD);
    Usart2_SendCmd(Buffer);
    ESP8266_WaitAck();
    OutPutLogo();
    Usart2_SendCmd(CIPMUX);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
#endif   
    sprintf(Buffer,"%s\"%s\",\"%s\",%s",CIPSTART,TCP,SERVER,PORT);
    Usart2_SendCmd(Buffer);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
    Usart2_SendCmd(CIPMODE);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
    Usart2_SendCmd(CIPSEND);
    Delay_Ms(Delay_SendCmd);
    OutPutLogo();
}












