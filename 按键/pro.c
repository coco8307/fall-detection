#include "STC8A.H"
#include <stdio.h>
#include "intrins.h"
#define KeyPort P3


void delayms(unsigned int z)
{
	unsigned int x,i,j;
	for(x=z;x>0;x--)
	for(i=20;i>0;i--)
	for(j=90;j>0;j--);	
}

/*------------------------------------------------
                    串口初始化
------------------------------------------------*/
void InitUART(void)	  //串口设置	  
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xE0;		//设定定时初值
	T2H = 0xFE;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	IE2 = 0x01;                                  //使能串口中断
}  
/****************串行口1字节发送****************/
void UART_1SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);	   //若TI=0，在此等待
    TI = 0;	 
}
 
/****************串行口2字节发送****************/
void UART_2SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //若S2TI=0，在此等待
    S2CON&=~S2TI;	  //S2TI=0
}    
/****************串行口1字符发送****************/
void SendStr1(unsigned char *s)
{
 while(*s!='\0') //通过检测是否字符串末尾
  {
  UART_1SendOneByte(*s);
  s++;
  }
}
/****************串行口2字符发送****************/
void SendStr2(unsigned char *s)
{
 int wei=0;
 while(*s!='\0') //通过检测是否字符串末尾              
  {
	  UART_2SendOneByte(*s);
	  s++;
  }
}

unsigned char KeyScan(void)  //键盘扫描函数，使用行列反转扫描法
{
	unsigned char cord_h,cord_l;//行列值中间变量
	KeyPort=0x0f;            //行线输出全为0
	cord_h=KeyPort&0x0f;     //读入列线值
	if(cord_h!=0x0f)    //先检测有无按键按下
	{
		delayms(10);        //去抖
		if((KeyPort&0x0f)!=0x0f)
		{
			cord_h=KeyPort&0x0f;  //读入列线值
			KeyPort=cord_h|0xf0;  //输出当前列线值
			cord_l=KeyPort&0xf0;  //读入行线值
			while((KeyPort&0xf0)!=0xf0);//等待松开并输出	
			return(cord_h+cord_l);//键盘最后组合码值
		}
	}
	else
		return(0xff);     //返回该值
}

unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0xe7:return 'D';break;// 按下相应的键显示相对应的码值
  case 0xd7:return 'C';break;//
  case 0xb7:return 'B';break;//
  case 0x77:return 'A';break;//

  case 0xeb:return 'E';break;//
  case 0xdb:return '9';break;//
  case 0xbb:return '6';break;//
  case 0x7b:return '3';break;//

  case 0xed:return '0';break;//
  case 0xdd:return '8';break;//
  case 0xbd:return '5';break;//
  case 0x7d:return '2';break;//

  case 0xee:return 'F';break;//
  case 0xde:return '7';break;//
  case 0xbe:return '4';break;//
  case 0x7e:return '1';break;//

  default:return 0xff;break;
 }
}



/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
	int i=0;
	unsigned char buf=0;
	InitUART();

	delayms(100);

	while(1)
	{
		i++;
		delayms(10);

		buf=KeyPro();
		if(buf!=0xff)
		UART_2SendOneByte(buf);
	}
}


void UART2_Isr() interrupt 8
{
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;                         //清中断标志
    }
}


