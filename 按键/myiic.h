#ifndef __MYIIC_H
#define __MYIIC_H
#include "STC8A.H"
#define u8 unsigned char
#define u16 unsigned int

//IO��������	 

sbit IIC1_SCL=P1^5;
sbit IIC1_SDA=P1^4;
sbit READ_SDA1=P1^4;
   	   		   
//IO��������
#define SDA1_IN()  {IIC1_SDA= 1;}



//IIC���в�������
void IIC1_Init(void);                //��ʼ��IIC��IO��				 
void IIC1_Start(void);				//����IIC��ʼ�ź�
void IIC1_Stop(void);	  			//����IICֹͣ�ź�
void IIC1_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC1_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC1_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC1_Ack(void);					//IIC����ACK�ź�
void IIC1_NAck(void);				//IIC������ACK�ź�

#endif
















