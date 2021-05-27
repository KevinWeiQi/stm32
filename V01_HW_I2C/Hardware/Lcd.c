
#include "LCD.h"
#include "Font.h"
void LCD_delay(u32 count)
{
  u32 i=0;
  for(;i<count;i++);
}

void LCD_writeCmd(u16 cmd)
{ 
    GPIO_ResetBits(GPIOC,GPIO_Pin_8);  //RS
    GPIO_ResetBits(GPIOC,GPIO_Pin_9); //CS
    GPIO_Write(GPIOB,cmd);            //WR
    GPIO_ResetBits(GPIOC,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_9); 	
}

void LCD_writeData(u16 dat)
{   
    GPIO_SetBits(GPIOC,GPIO_Pin_8);   //RS
    GPIO_ResetBits(GPIOC,GPIO_Pin_9); //CS
    GPIO_Write(GPIOB,dat);            //WR
    GPIO_ResetBits(GPIOC,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_7);    
    GPIO_SetBits(GPIOC,GPIO_Pin_9); 
}

void LCD_setScanDirection(void)
{
    u16 regval=0;
            //  MY      MX     MV     BGR
    regval|=((0<<7)|(0<<6)|(0<<5)|(1<<3)); 
    LCD_writeCmd(0x36);  
    LCD_writeData(regval);  
}

void LCD_setCursor(u16 xPos,u16 yPos)
{
	LCD_writeCmd(0x2A); 
	LCD_writeData(xPos>>8);
	LCD_writeData(xPos&0xFF);
	LCD_writeCmd(0x2B); 
	LCD_writeData(yPos>>8);
	LCD_writeData(yPos&0xFF);
}

void LCD_clear(u16 colour)
{
    u16 x;
    u16 y;
    for(y=0;y<=320;y++)
    {   
        for(x=0;x<=240;x++)
        {
            LCD_setCursor(x,y); //写GRAM指令，支持连续写
            LCD_writeCmd(0x2C);   
            LCD_writeData(colour);

        }
    }
}






void LCD_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //使能PORTB,C时钟和AFIO时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//开启SWD，失能JTAG

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;	   ///PORTC6~10复用推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //GPIOC	

    GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	//  PORTB推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOB

    GPIO_SetBits(GPIOB,GPIO_Pin_All);
    
    LCD_writeCmd(0x0000);  
    LCD_writeData(0x0001);
    
    // Initial code
    LCD_writeCmd(0xCF);  
    LCD_writeData(0x00); 
    LCD_writeData(0xC1); 
    LCD_writeData(0X30); 
    LCD_writeCmd(0xED);  
    LCD_writeData(0x64); 
    LCD_writeData(0x03); 
    LCD_writeData(0X12); 
    LCD_writeData(0X81); 
    LCD_writeCmd(0xE8);  
    LCD_writeData(0x85); 
    LCD_writeData(0x10); 
    LCD_writeData(0x7A); 
    LCD_writeCmd(0xCB);  
    LCD_writeData(0x39); 
    LCD_writeData(0x2C); 
    LCD_writeData(0x00); 
    LCD_writeData(0x34); 
    LCD_writeData(0x02); 
    LCD_writeCmd(0xF7);  
    LCD_writeData(0x20); 
    LCD_writeCmd(0xEA);  
    LCD_writeData(0x00); 
    LCD_writeData(0x00); 
    LCD_writeCmd(0xC0);    //Power control 
    LCD_writeData(0x1B);   //VRH[5:0] 
    LCD_writeCmd(0xC1);    //Power control 
    LCD_writeData(0x01);   //SAP[2:0];BT[3:0] 
    LCD_writeCmd(0xC5);    //VCM control 
    LCD_writeData(0x30); 	 //3F
    LCD_writeData(0x30); 	 //3C
    LCD_writeCmd(0xC7);    //VCM control2 
    LCD_writeData(0XB7); 
    LCD_writeCmd(0x36);    // Memory Access Control 
    LCD_writeData(0x48); 
    LCD_writeCmd(0x3A);   
    LCD_writeData(0x55); 
    LCD_writeCmd(0xB1);   
    LCD_writeData(0x00);   
    LCD_writeData(0x1A); 
    LCD_writeCmd(0xB6);    // Display Function Control 
    LCD_writeData(0x0A); 
    LCD_writeData(0xA2); 
    LCD_writeCmd(0xF2);    // 3Gamma Function Disable 
    LCD_writeData(0x00); 
    LCD_writeCmd(0x26);    //Gamma curve selected 
    LCD_writeData(0x01); 
    LCD_writeCmd(0xE0);    //Set Gamma 
    LCD_writeData(0x0F); 
    LCD_writeData(0x2A); 
    LCD_writeData(0x28); 
    LCD_writeData(0x08); 
    LCD_writeData(0x0E); 
    LCD_writeData(0x08); 
    LCD_writeData(0x54); 
    LCD_writeData(0XA9); 
    LCD_writeData(0x43); 
    LCD_writeData(0x0A); 
    LCD_writeData(0x0F); 
    LCD_writeData(0x00); 
    LCD_writeData(0x00); 
    LCD_writeData(0x00); 
    LCD_writeData(0x00); 		 
    LCD_writeCmd(0XE1);    //Set Gamma 
    LCD_writeData(0x00); 
    LCD_writeData(0x15); 
    LCD_writeData(0x17); 
    LCD_writeData(0x07); 
    LCD_writeData(0x11); 
    LCD_writeData(0x06); 
    LCD_writeData(0x2B); 
    LCD_writeData(0x56); 
    LCD_writeData(0x3C); 
    LCD_writeData(0x05); 
    LCD_writeData(0x10); 
    LCD_writeData(0x0F); 
    LCD_writeData(0x3F); 
    LCD_writeData(0x3F); 
    LCD_writeData(0x0F); 
    LCD_writeCmd(0x2B); 
    LCD_writeData(0x00);
    LCD_writeData(0x00);
    LCD_writeData(0x01);
    LCD_writeData(0x3f);
    LCD_writeCmd(0x2A); 
    LCD_writeData(0x00);
    LCD_writeData(0x00);
    LCD_writeData(0x00);
    LCD_writeData(0xef);	 
    LCD_writeCmd(0x11); //Exit Sleep
    LCD_delay(300000);
    LCD_writeCmd(0x29); //display on	
    
    LCD_setScanDirection();
    LCD_clear(BLACK);  //Initial background


}





void LCD_showCharacter(u16 x,u16 y,char *character,u16 colour)
{
	u8 i,j,index,temp_character;
	u16 temp_y=y;
	u8 mask=0x80;
	index=(*character-' ');
	for(j=0;j<16;j++)   //列
		{
			for(i=0;i<8;i++)       //行
				{
					temp_character=asc2_1608[index][j];
					LCD_setCursor(x,y);
					if(temp_character&mask)
						{
							LCD_writeCmd(0x2C);
				      		LCD_writeData(colour);	
						}
					mask=mask>>1;
					y++;
				}
			mask=0x80;
			if(y-temp_y==16)
				{
					y=temp_y;
					x++;
				}
		}
}


void LCD_showString(u16 x,u16 y,u16 colour,char *string)
{
	while((*string<='~')&&(*string>=' '))
		{
			LCD_showCharacter(x,y,string,colour);
			x=x+8;
            if(x>=240)
            {
                y=y+16;
                x=0;
            }
            else
            {
                y=y;
            }
		    string++;
		}   
}


void LCD_showMenu(u16 pen)
{
    u16 x;
    u16 y;
    for(y=0;y<=320;y++)
    {   
        for(x=0;x<=240;x++)
        {
            
            LCD_setCursor(x,y); //写GRAM指令，支持连续写
            LCD_writeCmd(0x2C);   
            if(x%60==0)
            {
                LCD_writeData(pen);
            }
        }
    }  
    for(x=0;x<=240;x++)
    {   
        for(y=0;y<=320;y++)
        {
            LCD_setCursor(x,y); //写GRAM指令，支持连续写
            LCD_writeCmd(0x2C);   
            if(y%80==0)
            {
                LCD_writeData(pen);
            }
        }
    } 
    //LCD show items
    LCD_showString(18,32,RED,"LED");
    LCD_showString(78,32,RED,"I2C");
    LCD_showString(138,32,RED,"SPI");
    LCD_showString(198,32,RED,"ADC");
    
    LCD_showString(14,112,RED,"FLSH");
    LCD_showString(74,112,RED,"TEMP");
    LCD_showString(134,112,RED,"UART");
    LCD_showString(194,112,RED,"INFR");   
}

void LCD_drawRectangle(u16 x,u16 y,u16 colour,u8 length,u8 width)
{
    u16 i,j;
    for(j=y;j<=(y+width);j++)
    { 
        for(i=x;i<=(x+length);i++)
        {
            LCD_setCursor(i,j);          //写GRAM指令，支持连续写
            LCD_writeCmd(0x2C);  
            LCD_writeData(colour);
        }
    }     
}











