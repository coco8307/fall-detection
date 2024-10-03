#ifndef __MYIIC_H
#define __MYIIC_H
#include "STC8A.H"
#define u8 unsigned char
#define u16 unsigned int

//IO操作函数	 

sbit IIC1_SCL=P1^5;
sbit IIC1_SDA=P1^4;
sbit READ_SDA1=P1^4;
   	   		   
//IO方向设置
#define SDA1_IN()  {IIC1_SDA= 1;}



//IIC所有操作函数
void IIC1_Init(void);                //初始化IIC的IO口				 
void IIC1_Start(void);				//发送IIC开始信号
void IIC1_Stop(void);	  			//发送IIC停止信号
void IIC1_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC1_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC1_Wait_Ack(void); 				//IIC等待ACK信号
void IIC1_Ack(void);					//IIC发送ACK信号
void IIC1_NAck(void);				//IIC不发送ACK信号

#endif
















