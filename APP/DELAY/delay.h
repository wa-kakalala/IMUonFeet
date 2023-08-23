#ifndef _DELAY_H_
#define _DELAY_H_
#include "system.h"
#include "misc.h"

void SysTick_Init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif

