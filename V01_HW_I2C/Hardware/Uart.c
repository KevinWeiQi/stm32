

#include "Uart.h"	
#include "stdio.h"	
#include "Uart2.h"

//重定向C库函数printf到串口
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

#endif
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
 
		USART_SendData(USART1, (uint8_t) ch);
		
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
    
	return ch;
}

int fgetc(FILE *f)
{
		
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}


void Uart_Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能UART1，GPIOA时钟

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    //USART1_RX	  GPIOA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

    //Usart1 NVIC 
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//初始化VIC寄存器

    //USART 

    USART_InitStructure.USART_BaudRate = bound;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据控制流
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//手法模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接收中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1 
}  

void Usart1_SendCmd(char *str)
{
    while(*str!='\0')
        {
            USART_SendData(USART1,*str);        
            while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET);  
            str++;
        }
}

void OutPutLogo(void)
{
    u16 i;
    if(1==Flag_RxFinish)
    {
           printf("Index=%d\r\n",Index_Recive);
           for(i=0;i<=(Index_Recive-1);i++)
            {
                USART_SendData(USART1, Buffer_RX[i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
           Flag_RxFinish=0;
           Index_Recive=0;
    }
}


u8 hexToChar(u8 dat)
{
    //char cdat;
    u8 cdat;
    //if ((dat >= 0) && (dat <= 9))
    if (dat <= 9)
    {
        cdat = dat + '0';
    }
    else if((dat >= 0xA) && (dat <= 0xF))
    {
        cdat = dat + 'a' - 10;
    }
    else
    {
        
    }
    return cdat;
}

void SendString(u8 dat)
{
    u8 Hbit;
    u8 Lbit;
    Hbit=(dat&0xF0)>>4;
	Lbit=dat&0xF;
	USART_SendData(USART1,hexToChar(Hbit));
    while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET); 
	USART_SendData(USART1,hexToChar(Lbit));
    while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET); 
}




void USART1_IRQHandler(void) 
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)
    {

    }
}


