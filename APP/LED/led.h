#ifndef __LED_H
#define	__LED_H

#include "system.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define  LED_PORT   	GPIOC
#define  LED_PIN    	GPIO_Pin_13
#define  LED_RCC    	RCC_APB2Periph_GPIOC
#define  LED_PIN_NUM	13

#define  ON_MODE    0       // when led is on  , the state of control pin
#define  OFF_MODE   1       // when led is off , the state of control pin

#define  LED_on()   (PCout(LED_PIN_NUM) = ON_MODE )   // led on   attention !!! here use LED_PIN_NUM not LED_PIN
#define  LED_off()  (PCout(LED_PIN_NUM) = OFF_MODE)   // led off


void LED_Init(void);

#endif /* __LED_H */
