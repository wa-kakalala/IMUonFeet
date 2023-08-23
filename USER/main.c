/**************************************
* filename    :  main.c
* author      :  wkk
* update time :  2023/8/21
*********************************************************/	
#include "led.h"
#include "delay.h"
#include "sonar_rx.h"
#include "usart3.h"

void SYS_Init(void){
	SystemInit();	    // config sys clk to 72M 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	SysTick_Init(72);
	LED_Init();       // Led Port Init
	SONAR_RX_Init();
	USART3_Init(115200);
}


int main(void)
{
	SYS_Init();
	LED_on();         // can use led to instruct that system is running
	
	
	printf("the system is running...\r\n");
  while (1)
  {
		LED_on();
		delay_ms(1000);
		LED_off();
		delay_ms(1000);
  }
}




