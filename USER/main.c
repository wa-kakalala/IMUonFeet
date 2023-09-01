/**************************************
* filename    :  main.c
* author      :  wkk
* update time :  2023/8/21
*********************************************************/	
#include "led.h"
#include "delay.h"
#include "sonar_rx.h"
#include "usart3.h"
#include "nrf24g.h"

void SYS_Init(void){
	SystemInit();	    // config sys clk to 72M 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	SysTick_Init(72);
	LED_Init();       // Led Port Init
	SONAR_RX_Init();
	USART3_Init(115200);
	NRF24G_Init();
}

int main(void)
{
	#ifdef DEBUG_MODE
	u32 led_counter = 0;
	#endif
	
	SYS_Init();
	#ifdef DEBUG_MODE
	printf("the system is running...\r\n");
	if( !NRF24G_Check() ){
		printf("the nrf24g device is ok !\r\n");
	}else{
		printf("the nrf24g device is error !!!\r\n");
	}
	#endif
	
	while (1)
	{
		#ifdef DEBUG_MODE
		// can use led to instruct that system is running
		if( led_counter == 300000 ) {
			 LED_on();
		}else if( led_counter == 600000 ) {
			 LED_off();
			 led_counter =0;
		}else {
		}
		led_counter ++;
		#endif
	}
}




