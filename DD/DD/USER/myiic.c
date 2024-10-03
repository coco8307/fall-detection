#include "myiic.h"
 
//��ʼ��IIC
void IIC1_Init(void)
{					     
	RCC->APB2ENR|=1<<3;//��ʹ������IO PORTBʱ�� 							 
	GPIOB->CRL&=0X00FFFFFF;//PB6/7 ������� 
	GPIOB->CRL|=0X33000000;	
	IIC1_SCL = 1;   
	
	IIC1_SDA = 1;   
}
//����IIC��ʼ�ź�
void IIC1_Start(void)
{
	SDA_OUT1();     //sda�����
	IIC1_SDA=1;	  	  
	IIC1_SCL=1;
	delay_us(4);
 	IIC1_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC1_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	delay_us(4);
}	  
//����IICֹͣ�ź�
void IIC1_Stop(void)
{
	SDA_OUT1();//sda�����
	IIC1_SCL=0;
	IIC1_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC1_SCL=1; 
	delay_us(4);
	IIC1_SDA=1;//����I2C���߽����ź�	
						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC1_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN1();      //SDA����Ϊ����  
	IIC1_SDA=1;
	delay_us(1);	   
	IIC1_SCL=1;
	delay_us(1);	 
	while(READ_SDA1)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC1_Stop();
			return 1;
		}
	}
	IIC1_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC1_Ack(void)///2
{
	IIC1_SCL=0;
	SDA_OUT1();
	IIC1_SDA=0;
	delay_us(2);
	IIC1_SCL=1;
	delay_us(2);
	IIC1_SCL=0;
}
//������ACKӦ��		    
void IIC1_NAck(void)
{
	IIC1_SCL=0;
	SDA_OUT1();
	IIC1_SDA=1;
	delay_us(2);
	IIC1_SCL=1;
	delay_us(2);
	IIC1_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC1_Send_Byte(u8 txd)
{                        
	u8 t;   
	SDA_OUT1(); 	    
	IIC1_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{              
		IIC1_SDA=(txd&0x80)>>7;
		txd<<=1; 	  
		delay_us(2);   
		IIC1_SCL=1;
		delay_us(2); 
		IIC1_SCL=0;	
		delay_us(2);
	}
    
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC1_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN1();//SDA����Ϊ����
  for(i=0;i<8;i++ )
	{
    IIC1_SCL=0; 
    delay_us(2);
		IIC1_SCL=1;
    receive<<=1;
    if(READ_SDA1)
			receive++;   
		delay_us(1); 
   }					 
   if(!ack)
     IIC1_NAck();//����nACK
   else
     IIC1_Ack(); //����ACK   
   return receive;
}



























