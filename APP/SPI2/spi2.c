#include "spi2.h"

/**
* SPI2 Init
* PB13 SPI2_SCK
* PB14 SPI2_MISO
* PB15 SPI2_MOSI
*/
void SPI2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	/* SPI IO and SPI clk enable */
  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	/* SPI IO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15 AF_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // Data mode : 1 line or 2 lines
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		// master
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		// 8-bit frame
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//  
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		// NSS pin
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	// MSB
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC
	SPI_Init(SPI2, &SPI_InitStructure);  
	
	SPI_Cmd(SPI2, ENABLE); 
	//SPI2_ReadWriteByte(0xff);
}

//SPI2 Set Speed
//SPI Speed =fAPB1/pre
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB1 -> 36Mhz:
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;
	SPI_Cmd(SPI2,ENABLE); //enable SPI2
} 

//SPI2 Write and Read 1 byte
//TxData: the data to send
//return: the value to read
u8 SPI2_ReadWriteByte(u8 TxData)
{		 			 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, TxData); 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI2);
}

// write const length data to address
// reg :  address
// pBuf:  data
// len :  datalen
u8 SPI2_Write_Buf(u8 reg,u8 *pBuf,u8 len){
		u8 index = 0;
	  u8 status = 0;
		status = SPI2_ReadWriteByte(reg);
	  for( index = 0;index<len;index++) {
			SPI2_ReadWriteByte(*pBuf++);
		}
		
		return status;
}

// read const length data from address
// reg :  address
// pBuf:  data
// len :  datalen
u8 SPI2_Read_Buf(u8 reg,u8 *pBuf,u8 len){
		u8 index = 0;
	  u8 status = 0;
		status = SPI2_ReadWriteByte(reg);
	  for( index = 0;index<len;index++) {
			pBuf[index] = SPI2_ReadWriteByte(0xff);
		}
		
		return status;
}


//SPIÐ´¼Ä´æÆ÷
//reg:Ö¸¶¨¼Ä´æÆ÷µØÖ·
//value:Ð´ÈëµÄÖµ
u8 SPI2_Write_Reg(u8 reg,u8 value)
{
		u8 status;	
  	status =SPI2_ReadWriteByte(reg);//·¢ËÍ¼Ä´æÆ÷ºÅ 
  	SPI2_ReadWriteByte(value);      //Ð´Èë¼Ä´æÆ÷µÄÖµ
  	return status;       			      //·µ»Ø×´Ì¬Öµ
}


//¶ÁÈ¡SPI¼Ä´æÆ÷Öµ
//reg:Òª¶ÁµÄ¼Ä´æÆ÷
u8 SPI2_Read_Reg(u8 reg)
{
	u8 reg_val;	    	
  SPI2_ReadWriteByte(reg);   //·¢ËÍ¼Ä´æÆ÷ºÅ
  reg_val=SPI2_ReadWriteByte(0XFF);//¶ÁÈ¡¼Ä´æÆ÷ÄÚÈÝ    
  return reg_val;           //·µ»Ø×´Ì¬Öµ
}	
