/******************* ********************
 * filename  £ºled.c
 * desc      £ºled operator library
 *          
 * platform  : STM32F103C8T6
 *          hardware connection
 *           -----------------
 *          |   PC13 - LED1   |
 *          |       
 *          |                 |
 *           ----------------- 								  
****************************************/
#include "led.h"


/**
* LED Init
*/
void LED_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( LED_RCC, ENABLE);        // enable led port clk
  GPIO_InitStructure.GPIO_Pin = LED_PIN;	         // select pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // set output mode : push pull mode      
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);        // init led 
  LED_off();                                       // turn off the led
}



