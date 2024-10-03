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



//IIC���в�������
void IIC1_Init(void);                //��ʼ��IIC��IO��				 
void IIC1_Start(void);				//����IIC��ʼ�ź�
void IIC1_Stop(void);	  			//����IICֹͣ�ź�
void IIC1_Send_Byte(unsigned char txd);			//IIC����һ���ֽ�
unsigned char IIC1_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
unsigned char IIC1_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC1_Ack(void);					//IIC����ACK�ź�
void IIC1_NAck(void);				//IIC������ACK�ź�

#endif
















