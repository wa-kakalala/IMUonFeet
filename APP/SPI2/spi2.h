#ifndef _SPI2_H_
#define _SPI2_H_

#include "system.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"


void SPI2_Init(void);			
void SPI2_SetSpeed(u8 SpeedSet); // set SPI2 speed
u8 SPI2_ReadWriteByte(u8 TxData);// SPI2 read and write one byte
u8 SPI2_Write_Buf(u8 reg,u8 *pBuf,u8 len);
u8 SPI2_Read_Buf(u8 reg,u8 *pBuf,u8 len);
u8 SPI2_Write_Reg(u8 reg,u8 value);
u8 SPI2_Read_Reg(u8 reg);

#endif


