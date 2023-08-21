/**************************************
* filename    :  main.c
* author      :  wkk
* update time :  2023/8/21
*********************************************************/	

#include "led.h"

void SYS_Init(void){
	SystemInit();	    // config sys clk to 72M 	
	LED_Init();       // Led Port Init
}


int main(void)
{
	SYS_Init();
	LED_on();         // can use led to instruct that system is running
	
  while (1)
  {
		
  }
}




