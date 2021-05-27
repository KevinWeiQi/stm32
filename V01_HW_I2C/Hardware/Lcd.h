#ifndef __LCD_H__
#define __LCD_H__

#include "stm32f10x.h"



//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ 
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)



void LCD_init(void);
void LCD_showCharacter(u16 x,u16 y,char *character,u16 colour);
void LCD_showString(u16 x,u16 y,u16 colour,char *string);
void LCD_showMenu(u16 pen);
void LCD_drawRectangle(u16 x,u16 y,u16 colour,u8 length,u8 width);
void LCD_clear(u16 colour);



#endif
