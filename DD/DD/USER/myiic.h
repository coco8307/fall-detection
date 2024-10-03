#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
   	   		   
#define SDA_IN1()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
#define SDA_OUT1() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}
	 
#define IIC1_SCL    PBout(6) //SCL
#define IIC1_SDA    PBout(7) //SDA	 
#define READ_SDA1   PBin(7)  // 



//IIC所有操作函数
void IIC1_Init(void);                //初始化IIC的IO口				 
void IIC1_Start(void);				//发送IIC开始信号
void IIC1_Stop(void);	  			//发送IIC停止信号
void IIC1_Send_Byte(unsigned char txd);			//IIC发送一个字节
unsigned char IIC1_Read_Byte(unsigned char ack);//IIC读取一个字节
unsigned char IIC1_Wait_Ack(void); 				//IIC等待ACK信号
void IIC1_Ack(void);					//IIC发送ACK信号
void IIC1_NAck(void);				//IIC不发送ACK信号

#endif
















