#include "show.h"
#include "OLED12864.h"
#include "usart2.h"
#include "delay.h"

u8 send_flag=0;
extern char No_dat[16];
extern int secsec;

void UART_2SendOneByte(unsigned char c)	   //串行口2字节发送
{
    USART2->DR=c;
	while((USART2->SR&0X40)==0);
	delay_us(10);
} 

void SendStr2(unsigned char *s)			   //串行口2字符发送
{
 while(*s!='\0') //通过检测是否字符串末尾              
  {
	  UART_2SendOneByte(*s);
	  s++;
  }
}

void SEND_MSG()							   //发送短信
{
	 OLED_CLS();
//	 OLED_ShowStr(0,0,"Send MSG...");
	 delay_ms(100);
	 SendStr2("AT+CMGF=1\r\n");
	 delay_ms(1000);
	 SendStr2("AT+CMGS=");
	 SendStr2(No_dat);
	 delay_ms(1000);

	 delay_ms(1000);
	 delay_ms(1000);

	 SendStr2("The old man fell dowm.");
	 

	 SendStr2("\r\n");
	 UART_2SendOneByte(0x1a);
	 OLED_CLS();
}

void oled_show(void)
{
		
		u8 flag_beep=0;							//OLED显示
		unsigned int  A1=0,B1=0;
		OLED_ShowStr(0,2,"Angle");
		if(Angle_Balance<0)	Angle_Balance+=360;		  
		A1=Angle_Balance;				 //pitch(X)
		OLED_ShowNum(45,2,A1,3);
		Angle_Balance1-=90;
		if(Angle_Balance1<0)		Angle_Balance1+=360;	 
		B1=Angle_Balance1;				 //roll(Y)
		OLED_ShowNum(90,2,B1,3);

		OLED_ShowNum(0,3,Gyro_Balance,3);
		OLED_ShowNum(45,3,Gyro_Turn,3);
		OLED_ShowNum(90,3,secsec,3);
		
		if(Gyro_Turn>450|Gyro_Balance>600)		 //跌倒检测
		{
			if((A1>40)&(A1<320))
			{
				BEEP=1;
				LED1=1;
				secsec=0;
			}
			if((B1>40)&(B1<320))
			{
				BEEP=1;
				LED1=1;
				secsec=0;
			}
		}
		if(send_flag==0)
		{
			if(secsec==10)
			{
				SEND_MSG();
				send_flag=1;
			}
			else {}
		}
}


