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
                    ���ڳ�ʼ��
------------------------------------------------*/
void InitUART(void)	  //��������	  
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xE0;		//�趨��ʱ��ֵ
	T2H = 0xFE;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	IE2 = 0x01;                                  //ʹ�ܴ����ж�
}  
/****************���п�1�ֽڷ���****************/
void UART_1SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);	   //��TI=0���ڴ˵ȴ�
    TI = 0;	 
}
 
/****************���п�2�ֽڷ���****************/
void UART_2SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //��S2TI=0���ڴ˵ȴ�
    S2CON&=~S2TI;	  //S2TI=0
}    
/****************���п�1�ַ�����****************/
void SendStr1(unsigned char *s)
{
 while(*s!='\0') //ͨ������Ƿ��ַ���ĩβ
  {
  UART_1SendOneByte(*s);
  s++;
  }
}
/****************���п�2�ַ�����****************/
void SendStr2(unsigned char *s)
{
 int wei=0;
 while(*s!='\0') //ͨ������Ƿ��ַ���ĩβ              
  {
	  UART_2SendOneByte(*s);
	  s++;
  }
}

unsigned char KeyScan(void)  //����ɨ�躯����ʹ�����з�תɨ�跨
{
	unsigned char cord_h,cord_l;//����ֵ�м����
	KeyPort=0x0f;            //�������ȫΪ0
	cord_h=KeyPort&0x0f;     //��������ֵ
	if(cord_h!=0x0f)    //�ȼ�����ް�������
	{
		delayms(10);        //ȥ��
		if((KeyPort&0x0f)!=0x0f)
		{
			cord_h=KeyPort&0x0f;  //��������ֵ
			KeyPort=cord_h|0xf0;  //�����ǰ����ֵ
			cord_l=KeyPort&0xf0;  //��������ֵ
			while((KeyPort&0xf0)!=0xf0);//�ȴ��ɿ������	
			return(cord_h+cord_l);//������������ֵ
		}
	}
	else
		return(0xff);     //���ظ�ֵ
}

unsigned char KeyPro(void)
{
 switch(KeyScan())
 {
  case 0xe7:return 'D';break;// ������Ӧ�ļ���ʾ���Ӧ����ֵ
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
                    ������
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
        S2CON &= ~S2RI;                         //���жϱ�־
    }
}


