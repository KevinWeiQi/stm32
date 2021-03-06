#ifndef __LCD_H__
#define __LCD_H__

#include "stm32f10x.h"



//画笔颜色
#define WHITE         	        0xFFFF
#define BLACK         	        0x0000	  
#define BLUE         	        0x001F  
#define BRED                   0XF81F
#define GRED 		        0XFFE0
#define GBLUE		        0X07FF
#define RED           	        0xF800
#define MAGENTA              0xF81F
#define GREEN         	        0x07E0
#define CYAN          	        0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色 
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)



void LCD_init(void);
void LCD_showCharacter(u16 x,u16 y,char *character,u16 colour);
void LCD_showString(u16 x,u16 y,u16 colour,char *string);
void LCD_showMenu(u16 pen);
void LCD_drawRectangle(u16 x,u16 y,u16 colour,u8 length,u8 width);
void LCD_clear(u16 colour);



#endif
