

#include "Uart2.h"	
#include "stdio.h"	
#include "gizwits_product.h"


u8 Flag_RxFinish=1;

char Buffer_RX[1024]={0};
u16 Index_Recive=0;



#if 0
#pragma import(__use_no_semihosting)             
             
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

_sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
 
		USART_SendData(USART2, (uint8_t) ch);
		
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
    
	return ch;
}


#endif

void Uart2_Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);


    //USART2_TX   GPIOA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART2_RX	  GPIOA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //Usart2 NVIC 
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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

    USART_Init(USART2, &USART_InitStructure); 
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);                    
}  

void Usart2_SendCmd(char *str)
{
    while(*str!='\0')
        {
            USART_SendData(USART2,*str);        
            while( USART_GetFlagStatus(USART2,USART_FLAG_TXE)== RESET);  
            str++;
        }
}

void USART2_IRQHandler(void) 
{
    u8 res;
#if 1
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
//        Buffer_RX[Index_Recive++]=USART_ReceiveData(USART2);
//        Flag_RxFinish=1;
//        
        res =USART_ReceiveData(USART2); 
        gizPutData(&res,1);
        
    }   

#endif  



    
}


