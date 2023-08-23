#include "delay.h"

// this is lost in this project
// SYSTICK_ENABLE is defined in core_cm3.h and the value is 0
#define SysTick_CTRL_ENABLE_Msk   (1ul << SYSTICK_ENABLE)                    /*!< SysTick CTRL: ENABLE Mask */

// when clk of systick is 9MHz ( HCLK/8) --> 1ms reference
static u32 fac_us;	// the timer value of 1us
static u32 fac_ms;	// the timer value of 1ms

/**
 * SysTick Init
 * SYSCLK : 72
 */
void SysTick_Init(u8 SYSCLK){
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// choose HCLK/8 = 72Mhz /8 = 9MHz
	fac_us = SYSCLK / 8;	//  72M/ 8M = 9, SystemCoreClock = 72MHz
	// current SysTick clk is 9MHz , just after 9 clk , the total time is 1us
	fac_ms = fac_us * 1000;						 // the timer value of 1ms
	
	// disable SysTick
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

/**
 * us leval delay function
 * max value 798915us
 * temp & 0x01 && !(temp & (1 << 16))
 * temp & 0x01 -> lowest bit to conduct whether timer is enable state
 * !(temp & (1 << 16))-> biggest bit ot conduct whether is zero state
 */
void delay_us(u32 nus){
	u32 temp;
	SysTick -> LOAD = nus * fac_us;		//reload value
	SysTick -> VAL |= 0x00;		// reset to 0
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;		// start timer
	// conduct whether is zero state
	do{
		temp = SysTick -> CTRL;	// timer state value
	}while(temp & 0x01 && !(temp & (1 << 16)));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;	// disable timer
	SysTick -> VAL |= 0x00;		//reset to 0
}

/**
 * ms leval delay function
 * max delay: 1864 ms
 */
void delay_ms(u32 nms){
	u32 temp;
	SysTick -> LOAD = nms * fac_ms;		
	SysTick -> VAL |= 0x00;		
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;		
	do{
		temp = SysTick -> CTRL;	
	}while(temp & 0x01 && !(temp & (1 << 16)));
	SysTick -> CTRL &= ~SysTick_CTRL_ENABLE_Msk;	
	SysTick -> VAL |= 0x00;	
}
