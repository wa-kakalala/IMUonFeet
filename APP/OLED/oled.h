#ifndef _OLED_H_
#define _OLED_H_

#include "system.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "font.h"

#define  OLED_SCL_PORT   	GPIOB
#define  OLED_SCL_PIN    	GPIO_Pin_8
#define  OLED_SCL_RCC    	RCC_APB2Periph_GPIOB
#define  OLED_SCL_PIN_NUM	8

#define  OLED_SDA_PORT   	GPIOB
#define  OLED_SDA_PIN    	GPIO_Pin_9
#define  OLED_SDA_RCC    	RCC_APB2Periph_GPIOB
#define  OLED_SDA_PIN_NUM	9

#define  OLED_SCL         	PBout(OLED_SCL_PIN_NUM)
#define  OLED_SDA         	PBout(OLED_SDA_PIN_NUM)

#define  SLAVE_ADDR       	0x78
#define  WRITE_CMD        	0x00
#define  WRITE_DATA       	0x40

#define OLED_CMD  	1	//Ð´ÃüÁî
#define OLED_DATA 	0	//Ð´Êý¾Ý

#define X_WIDTH  	128
#define Y_HEIGHT 	64

#define FONT_16  	16
#define FONT_12  	12

void OLED_Init(void);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 font);
void OLED_DrawPic(u8 x0, u8 y0,u8 w, u8 h,u8 pic[]);


#endif 

