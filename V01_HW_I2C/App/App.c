#include "App.h"
#include "Lcd.h"
#include "Key.h"
#include "Uart.h"
#include "Led.h"
#include "ADC.h"



          
const u16 buttom_xIndex[]={20, 80, 140, 200,  20,  80, 140, 200};
const u16 buttom_yIndex[]={55, 55,  55,  55, 135, 135, 135, 135};


u8 index_Key0=0;
u8 step=0;
u8 flag_lastButtom=0;
u8 flag_enterTestMode=0;
u8 flag_runOneCycle=0;


void menuInitial(void)
{
    LCD_showMenu(RED);                              //Initial Menu   
    LCD_drawRectangle(buttom_xIndex[0],buttom_yIndex[0],BLUE,20,20);   //Initial Buttom  
}

void clearLastButtom(u16 x,u16 y)
{
    LCD_drawRectangle(x,y,BLACK,20,20);   
         
}

void clearMenu(void)
{
    LCD_showMenu(BLACK);
}

void moduleTest(void)
{
            switch(step)
                {
                    case 0:                                //LED
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(80,10,WHITE,"LED Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                            Led_module();                     //user handle
                            if(1==KEY1_scan())
                            {
                                Led_moduleClear();
                            }
                            
                        break;
                    case 1:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(80,0,GREEN,"I2C Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break;
                    case 2:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(80,0,BLUE,"SPI Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break;
                    case 3:                                    //ADC
                            if(0==flag_runOneCycle)
                                {
                                LCD_clear(BLACK);
                                LCD_showString(80,0,YELLOW,"ADC Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                           
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                             ADC_dat();
                        break; 
                    case 4:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(76,0,GBLUE,"FLSH Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break;
                    case 5:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(76,0,MAGENTA,"TEMP Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break;
                    case 6:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(76,0,CYAN,"UART Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break;
                    case 7:
                            if(0==flag_runOneCycle)
                            {
                                LCD_clear(BLACK);
                                LCD_showString(76,0,BROWN,"INFR Module");
                                flag_enterTestMode=1;
                                flag_runOneCycle=1;
                            }
                            if(1==KEYUP_scan())
                            {
                                flag_runOneCycle=0;
                            }
                        break; 
                            
                }    
}


void buttonScan(void)
{
    
    if((1==KEY0_scan())&&(0==flag_enterTestMode))
        {
           if(1==flag_lastButtom)
                {
                    clearLastButtom(buttom_xIndex[7],buttom_yIndex[7]);                       
                    LCD_drawRectangle(buttom_xIndex[index_Key0],buttom_yIndex[index_Key0],BLUE,20,20);                  
                } 
            if(index_Key0>=1)
                {
                    clearLastButtom(buttom_xIndex[index_Key0-1],buttom_yIndex[index_Key0-1]);
                }   
            LCD_drawRectangle(buttom_xIndex[index_Key0],buttom_yIndex[index_Key0],BLUE,20,20); 
            step=index_Key0;
            index_Key0++;
            if(index_Key0>=8)
            {
                index_Key0=0;
                flag_lastButtom=1;
            }
        } 

      else if(1==KEYUP_scan())
        {
             //temp=temp;
             flag_enterTestMode=1;
        }
      else if(1==KEY1_scan())
        {
            LCD_clear(BLACK);
            LCD_showMenu(RED);
            if(7==step)
            {
                LCD_drawRectangle(buttom_xIndex[7],buttom_yIndex[7],BLUE,20,20);      
            }
            else
                {
                    if(0==index_Key0)
                    {
                        clearLastButtom(buttom_xIndex[index_Key0],buttom_yIndex[index_Key0]); 
                        LCD_drawRectangle(buttom_xIndex[index_Key0],buttom_yIndex[index_Key0],BLUE,20,20);                          
                    }  
                    else
                    {
                        clearLastButtom(buttom_xIndex[index_Key0-1],buttom_yIndex[index_Key0-1]); 
                        LCD_drawRectangle(buttom_xIndex[index_Key0-1],buttom_yIndex[index_Key0-1],BLUE,20,20);  
                    }
                   
                }
            flag_enterTestMode=0;
        }
    
}


void Function_scan(void)
{
    buttonScan();
    if(1==flag_enterTestMode)
        {
          moduleTest();
        }
}





















