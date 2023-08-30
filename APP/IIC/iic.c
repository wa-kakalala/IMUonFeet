#include "iic.h"
#include "delay.h"

/***********************
* SCL: PB8
* SDA: PB9
***********************/
void IIC_Init(){			
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SCL_RCC, ENABLE);			     
 	GPIO_InitStructure.GPIO_Pin = SCL_PIN | SDA_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_PORT, &GPIO_InitStructure);
	
	IIC_SCL = 1;
	IIC_SDA = 1;
}

/***********************
* IIC Start Signal
***********************/
void IIC_Start(){
	IIC_SCL = 1;
	IIC_SDA = 1;
	delay_us(5);
 	IIC_SDA = 0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL = 0;
}

/***********************
* IIC Stop Signal
***********************/  
void IIC_Stop()
{
	IIC_SCL = 1;
	IIC_SDA = 0;  //STOP:when CLK is high DATA change form low to high
	delay_us(4);
	IIC_SDA = 1;
	delay_us(5);		   	
}

/***********************
* IIC_Wait_Ack
***********************/  
void IIC_Wait_Ack(void)
{
	IIC_SDA = 1;
	IIC_SCL = 0;
	delay_us(4);		 
	IIC_SCL = 1;
	delay_us(4);		
	IIC_SCL = 0;
} 

/***********************
* IIC_Send_Byte
***********************/    
void IIC_Send_Byte(u8 txd)
{                        
	u8 t;     
	IIC_SCL = 0;
	for(t=0;t<8;t++){              
		IIC_SDA= txd & ( 0x80 >> t );	  
		delay_us(3);   
		IIC_SCL=1;
		delay_us(5);
		IIC_SCL=0;	
		delay_us(2);
	}	 
} 

/***********************
* IIC Write Bytes
* dev : devices 7 bits
* reg : aim reg address
* data : the data to send
* length : byte length
***********************/
void IIC_WriteBytes(u8 dev, u8 reg,u8* data, u8 length){
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev<<1);
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_Send_Byte(data[count]); 
		IIC_Wait_Ack(); 
	}
	IIC_Stop();
}

