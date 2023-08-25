#include "nrf24g.h"

/**
* PA1-> NRF IRQ
*/
void NRF_IRQ_Init(){
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);           // AFIO Enable
	
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_1;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  //下拉输入  
	GPIO_Init(GPIOA,&GPIO_InitStructure);		     /* 初始化GPIO */
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);   //选择GPIO管脚用作外部中断线路
	
	//EXTI0 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//EXTI0中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void NRF24G_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI2_Init();
	NRF_IRQ_Init();
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4); // set SPI2 speed 9M, nrf24l01->max 10M
	
  RCC_APB2PeriphClockCmd( NRF_CE_RCC, ENABLE);        // enable led port clk
  GPIO_InitStructure.GPIO_Pin = NRF_CE_PIN;	          // select pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // set output mode : push pull mode      
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(NRF_CE_PORT, &GPIO_InitStructure);        // init led 
	
	RCC_APB2PeriphClockCmd( NRF_CS_RCC, ENABLE);        // enable led port clk
  GPIO_InitStructure.GPIO_Pin = NRF_CS_PIN;	          // select pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // set output mode : push pull mode      
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(NRF_CS_PORT, &GPIO_InitStructure);        // init led 
	// set CE to 0
	NRF_CE_LOW();
	
	// set CS to 1
	NRF_CS_HIGH();
}

// Check NRF24G's Status
// 0 --> ok
// 1 --> error
u8 NRF24G_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i = 0;
	NRF_CS_LOW();	 
	SPI2_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	SPI2_Write_Buf(TX_ADDR,buf,5); //读出写入的地址  
	NRF_CS_HIGH();
	for(i=0;i<5;i++) if(buf[i]!=0XA5) return 1;	 							   
	return 0;		 
}	


const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01};

/**
* RX Mode
* 0x0f: 0000 1111 
* 0x3f: 0011 1111 RX Intruption only
*/
void NRF24L01_RX_Mode()
{
	NRF_CE_LOW();  
	NRF_CS_LOW();	
  SPI2_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
  SPI2_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
  SPI2_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
  SPI2_Write_Reg(NRF_WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
  SPI2_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
  SPI2_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  SPI2_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);  //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  NRF_CS_HIGH();
	NRF_CE_HIGH();
}	

/**
* TX Mode with no auto resend
* 0x0e: 0000 1110
* 0x5e: 0101 1110  TX Intruption only
*/
void NRF24L01_TX_Mode()
{														 
	NRF_CE_LOW();  
	NRF_CS_LOW();	    
  SPI2_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);    //写TX节点地址 
  SPI2_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

  SPI2_Write_Reg(NRF_WRITE_REG+EN_AA,0x00);     // disable 
  SPI2_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  SPI2_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x00);// disable
  SPI2_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
  SPI2_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  SPI2_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF_CS_HIGH();
	NRF_CE_HIGH();
}


void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==1)
	{
		#ifdef DEBUG_MODE
		printf("EXTI 1 is get...\r\n");
		#endif
		
		
		
		
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}




