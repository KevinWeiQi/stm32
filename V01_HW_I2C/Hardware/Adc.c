


#include "Adc.h"
#include "Delay.h"
#include "LCD.h"
#include "stdio.h"
#include "UART.h"


void  ADC_init(void)
{ 	
	ADC_InitTypeDef ADC_initStructure; 
	GPIO_InitTypeDef GPIO_initStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_initStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_initStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_initStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_initStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_initStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_initStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_initStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_initStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}


u16 ADC_getValue(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}


void ADC_dat(void)
{
    char buffer_value[10];
    char buffer_voltage[10];
    u16 value;
    float voltage;
    
    value=ADC_getValue(ADC_Channel_1);
    voltage=(float)value*(3.3/4095);
//    sprintf(buffer_value,"Value:%d",value);
//    sprintf(buffer_voltage,"Voltage:%4.3f",voltage);



    
    sprintf(buffer_value,"%d",value);
    sprintf(buffer_voltage,"%4.3f",voltage);
    
    LCD_drawRectangle(130,100,BLACK,40,16);
    LCD_drawRectangle(130,120,BLACK,40,16);
    
    LCD_showString(50,100,YELLOW,"Value:");
    LCD_showString(50,120,YELLOW,"Voltage:");
    
    LCD_showString(130,100,YELLOW,buffer_value);
    LCD_showString(130,120,YELLOW,buffer_voltage);
    Delay_Ms(6000000);
    
//    printf("%s\r\n",buffer_value);

}


