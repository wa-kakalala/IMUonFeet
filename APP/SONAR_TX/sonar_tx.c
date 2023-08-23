#include "sonar_tx.h"
#include "delay.h"

// sonar bind to PB0 and PC14
#ifdef SONAR_TX_DEFINE
SONAR_TX_PORTLIST_BEGIN
	GPIOB ,
	GPIOC 
SONAR_TX_PORTLIST_END

SONAR_TX_PINLIST_BEGIN
	GPIO_Pin_0,
	GPIO_Pin_14
SONAR_TX_PINLIST_END

SONAR_TX_RCCLIST_BEGIN
	RCC_APB2Periph_GPIOB,
	RCC_APB2Periph_GPIOC
SONAR_TX_RCCLIST_END
#endif

// SONAR TX Init
void SONAR_TX_Init(){
	u8 index = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	for(index = 0;;index++){
		if(!sonar_tx_port_list[index]) break;
		RCC_APB2PeriphClockCmd( sonar_tx_rcc_list[index], ENABLE);  // enable rcc
		GPIO_InitStructure.GPIO_Pin = sonar_tx_pin_list[index];	    // select pin
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            // set output mode : push pull mode  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(sonar_tx_port_list[index], &GPIO_InitStructure);  // init led 
		
		GPIO_ResetBits(sonar_tx_port_list[index],sonar_tx_pin_list[index]);
	}
}


// SONAR TX Init
// index : the index of Sonar Device
void SONAR_Launch(u8 index){
	GPIO_SetBits(sonar_tx_port_list[index],sonar_tx_pin_list[index]);
	delay_us(DELAY_US);
	GPIO_ResetBits(sonar_tx_port_list[index],sonar_tx_pin_list[index]);
}

