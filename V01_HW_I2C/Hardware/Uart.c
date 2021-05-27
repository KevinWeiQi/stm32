

#include "Uart.h"	
#include "stdio.h"	
#include "Uart2.h"

//�ض���C�⺯��printf������
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

#endif
//�ض���fputc���� 
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
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��UART1��GPIOAʱ��

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX	  GPIOA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

    //Usart1 NVIC 
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//��ʼ��VIC�Ĵ���

    //USART 

    USART_InitStructure.USART_BaudRate = bound;//������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ�����ݿ�����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�ַ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
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


