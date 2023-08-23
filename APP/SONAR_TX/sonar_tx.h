#ifndef _SONAR_TX_H_
#define _SONAR_TX_H_

#include "system.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define SONAR_TX_DEFINE 1

#ifdef SONAR_TX_DEFINE

#define SONAR_TX_PORTLIST_BEGIN      \
		GPIO_TypeDef * sonar_tx_port_list[] = { 

#define SONAR_TX_PORTLIST_END  ,0};

#define SONAR_TX_PINLIST_BEGIN       \
		uint16_t sonar_tx_pin_list[] = { 
	
#define SONAR_TX_PINLIST_END ,255};		

#define SONAR_TX_RCCLIST_BEGIN       \
		uint32_t sonar_tx_rcc_list[] = { 
	
#define SONAR_TX_RCCLIST_END ,0};	

#endif
		
#define DELAY_US 300

void SONAR_TX_Init(void);
void SONAR_Start(u8 index);

#endif

