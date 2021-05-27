
#include "I2C.h"
#include "Delay.h"



void I2C_init(void)
{	

    
    GPIO_InitTypeDef GPIO_InitStructure;

    FT_I2C_SDA_RCC_AHBPeriphClockCmd(FT_I2C_SDA_RCC_AHBPeriph,ENABLE);  
    GPIO_InitStructure.GPIO_Pin = FT_I2C_SDA_Pin|FT_I2C_SCL_Pin;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(FT_I2C_SDA_Port, &GPIO_InitStructure);
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);

}


void I2C_Start(void)
{
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin); 
    Delay_Ms(delay_I2cBus);
    GPIO_ResetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);   //��ʼ�ź�:SCLΪ�ߵ�ƽʱ��SDA�ɸ߱��
    Delay_Ms(delay_I2cBus);
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    Delay_Ms(delay_I2cBus);
}

void I2C_Stop(void)
{
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    GPIO_ResetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);    //�Ƚ�SCL,SDA���ֵ͵�ƽ
    Delay_Ms(delay_I2cBus);
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);      //����SCL
    Delay_Ms(delay_I2cBus);
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);       //��ֹ�ź�:SCLΪ�ߵ�ƽʱ��SDA�ɵͱ��

 
}

u8 I2C_Write(u8 dat)  //I2C����д������������Ӧ��״̬
{

        u8 ack;
		u8 i;
		for(i=0;i<8;i++)
		{
            if(dat&0x80)
            {
                GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);   
                Delay_Ms(delay_I2cBus); 
                 
            }
            else
            {
                GPIO_ResetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);  
                Delay_Ms(delay_I2cBus); 
            }
            dat<<=1;
            GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);              //����SCL����ס�ȴ���ȡ
            Delay_Ms(delay_I2cBus); 
            GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
		}
	
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);               //������8λ�����ͷ�����,���ACK
    Delay_Ms(delay_I2cBus); 
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
    Delay_Ms(delay_I2cBus); 
    ack=GPIO_ReadInputDataBit(FT_I2C_SDA_Port,FT_I2C_SDA_Pin); 
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);   
    Delay_Ms(delay_I2cBus); 
    
    return ack;   
}




u8 I2C_ReadNak(void) //I2C���߶������������ͷ�Ӧ���źţ����ض������ֽ�
{
    u8 dat=0;
    u8 mask =0;
    u8 i;
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);    //ȷ�������ͷ�SDA
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
    Delay_Ms(delay_I2cBus); 
	
	for (i = 0; i < 8; i++)
	{
        GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
        Delay_Ms(delay_I2cBus); 
		if (GPIO_ReadInputDataBit(FT_I2C_SDA_Port,FT_I2C_SDA_Pin))
		{
			mask=0x01;

		}
        else
        {
            mask=0x00;  
           
        }
        dat = (dat<<1)|mask; 
        GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
        Delay_Ms(delay_I2cBus);
	}
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin); //8λ���ݷ����������SDA�����ͷ�Ӧ���ź�
    Delay_Ms(delay_I2cBus); 
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);  //����SCL   
    Delay_Ms(delay_I2cBus); 
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);  //������SCL��ɷ�Ӧ��λ��������ס����
    return dat;   
    
}






























