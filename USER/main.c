/**************************************
* filename    :  main.c
* author      :  wkk
* update time :  2023/8/21
*********************************************************/	

#include "led.h"
#include "delay.h"

void SYS_Init(void){
	SystemInit();	    // config sys clk to 72M 	
	LED_Init();       // Led Port Init
	SysTick_Init(72);
}


int main(void)
{
	SYS_Init();
	LED_on();         // can use led to instruct that system is running
	
  while (1)
  {
		LED_on();
		delay_ms(1000);
		LED_off();
		delay_ms(1000);
  }
}




