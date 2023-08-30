#ifndef _IIC_H_
#define _IIC_H_

#include "system.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define  SCL_PORT   	GPIOB
#define  SCL_PIN    	GPIO_Pin_8
#define  SCL_RCC    	RCC_APB2Periph_GPIOB
#define  SCL_PIN_NUM	8

#define  SDA_PORT   	GPIOB
#define  SDA_PIN    	GPIO_Pin_9
#define  SDA_RCC    	RCC_APB2Periph_GPIOB
#define  SDA_PIN_NUM	9

#define  IIC_SCL      PBout(SCL_PIN_NUM)
#define  IIC_SDA      PBout(SDA_PIN_NUM)

void IIC_Init(void);
void IIC_WriteBytes(u8 dev, u8 reg,u8* data, u8 length);

#endif

