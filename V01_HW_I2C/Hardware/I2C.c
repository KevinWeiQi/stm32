
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
    GPIO_ResetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);   //起始信号:SCL为高电平时，SDA由高变低
    Delay_Ms(delay_I2cBus);
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    Delay_Ms(delay_I2cBus);
}

void I2C_Stop(void)
{
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);
    GPIO_ResetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);    //先将SCL,SDA保持低电平
    Delay_Ms(delay_I2cBus);
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);      //拉高SCL
    Delay_Ms(delay_I2cBus);
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);       //终止信号:SCL为高电平时，SDA由低变高

 
}

u8 I2C_Write(u8 dat)  //I2C总线写操作，并返回应答状态
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
            GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);              //拉高SCL保持住等待读取
            Delay_Ms(delay_I2cBus); 
            GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
		}
	
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);               //发送完8位数据释放总线,检测ACK
    Delay_Ms(delay_I2cBus); 
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin); 
    Delay_Ms(delay_I2cBus); 
    ack=GPIO_ReadInputDataBit(FT_I2C_SDA_Port,FT_I2C_SDA_Pin); 
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);   
    Delay_Ms(delay_I2cBus); 
    
    return ack;   
}




u8 I2C_ReadNak(void) //I2C总线读操作，并发送非应答信号，返回读到的字节
{
    u8 dat=0;
    u8 mask =0;
    u8 i;
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin);    //确保主机释放SDA
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
    GPIO_SetBits(FT_I2C_SDA_Port,FT_I2C_SDA_Pin); //8位数据发送完后，拉高SDA，发送非应答信号
    Delay_Ms(delay_I2cBus); 
    GPIO_SetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);  //拉高SCL   
    Delay_Ms(delay_I2cBus); 
    GPIO_ResetBits(FT_I2C_SCL_Port,FT_I2C_SCL_Pin);  //再拉低SCL完成非应答位，并保持住总线
    return dat;   
    
}






























