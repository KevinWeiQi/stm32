


#include "Adc.h"
#include "Delay.h"
#include "LCD.h"
#include "stdio.h"
#include "UART.h"


void  ADC_init(void)
{ 	
	ADC_InitTypeDef ADC_initStructure; 
	GPIO_InitTypeDef GPIO_initStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_initStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_initStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_initStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_initStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_initStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_initStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_initStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_initStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}


u16 ADC_getValue(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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


