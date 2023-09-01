#include "oled.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 	

// 图像取模方式：
// 1. 逆向：低位在前高位在后
// 2. 列行式
//    1  9
//    2  10
//    3  11
//    .
//    8  16

/**********************************************
* IIC Start
**********************************************/
void OLED_IIC_Start(){
	OLED_SCL = 1;
	OLED_SDA = 1;
	
	OLED_SDA = 0;
	OLED_SCL = 0;
}

/**********************************************
* IIC Stop
**********************************************/
void OLED_IIC_Stop(){
	OLED_SCL = 1;
	OLED_SDA = 0;
	OLED_SDA = 1;
}

void OLED_IIC_Wait_Ack(){
	OLED_SCL = 1;
	OLED_SCL = 0;
}

/**********************************************
* IIC Write byte
**********************************************/
void OLED_Write_IIC_Byte(unsigned char data)
{
	u8 i;
	OLED_SCL = 0;
	for(i=0;i<8;i++)		
	{
		OLED_SDA = (data >> (7-i)) & 0x01;
		OLED_SCL = 1;
		OLED_SCL = 0;
	}
}

/**********************************************
* IIC Write Command
**********************************************/
void Write_IIC_Command(u8 cmd)
{
	OLED_IIC_Start();
	OLED_Write_IIC_Byte(SLAVE_ADDR); //Slave address,SA0=0
	OLED_IIC_Wait_Ack();	
	OLED_Write_IIC_Byte(WRITE_CMD);			  //write command
	OLED_IIC_Wait_Ack();	
	OLED_Write_IIC_Byte(cmd); 
	OLED_IIC_Wait_Ack();	
	OLED_IIC_Stop();
}

/**********************************************
* IIC Write Data
**********************************************/
void Write_IIC_Data(u8 data){
	OLED_IIC_Start();
	OLED_Write_IIC_Byte(SLAVE_ADDR);			//D/C#=0; R/W#=0
	OLED_IIC_Wait_Ack();	
	OLED_Write_IIC_Byte(WRITE_DATA);			//write data
	OLED_IIC_Wait_Ack();	
	OLED_Write_IIC_Byte(data);
	OLED_IIC_Wait_Ack();	
	OLED_IIC_Stop();
}

/**********************************************
* IIC Write Data or Cmd
* cmd == 1 : write cmd
* cmd == 0 : write data
**********************************************/
void OLED_WR_Byte(u8 dat,u8 cmd)
{
	if(!cmd){
		Write_IIC_Data(dat);
	}
	else {
		Write_IIC_Command(dat);	
	}
}


/***********************
* SCL: PB8
* SDA: PB9
***********************/
void OLED_Init(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(OLED_SCL_RCC, ENABLE);			     
 	GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN | OLED_SDA_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_SCL_PORT, &GPIO_InitStructure);
	
	OLED_SCL = 1;
	OLED_SDA = 1;
	//delay_ms(800);
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}

//坐标设置
// x : 0~127
// y : 0~7
void OLED_Set_Pos(u8 x, u8 y) { 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   

//开启OLED显示    
void OLED_Display_On(){
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示     
void OLED_Display_Off(){
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		 

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte(0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte(0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte(0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++) OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		// 设置为0x01是一些条纹线，设置为0xff是全亮 
		for(n=0;n<128;n++)OLED_WR_Byte(0xff,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~7			 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 font)
{      	
	u8 c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>X_WIDTH-1){
		x=0;
		y=y+2;
	}
	if(font == 16){
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++) OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++) OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}else {	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		}
}

/**********************************************
* Show Picture
* Picture : 128 x 64
* x : 0 ~ 127
* y : 0 ~ 63  ****
* w : 0 ~ 128
* h : 0 ~ 64
* page : 0 ~ 7 
**********************************************/
void OLED_DrawPic(u8 x0, u8 y0,u8 w, u8 h,u8 pic[])
{ 	
	u32 j=0;
	u8 x,y,x1,y1;
	x1 = x0 + w;
	y1 = ( y0 + h ) >> 3;
	
	if( x1 > 128 ) x1 = 128;
	if( y1 > 8 )   y1 = 8;
	
	for(y = y0 >> 3 ;y<y1;y++){
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++){      
			OLED_WR_Byte(pic[j++],OLED_DATA);	    	
		}
	}
} 
	
