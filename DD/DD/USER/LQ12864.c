#include "OLED12864.h"
#include "codetab.h"

#define abs(x) ((x) > 0 ? (x) : -(x))

void delay_0(int c)   //��� 0us
{
   delay_ms(c);
}

/*********************OLEDд����************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC1_Start();
	IIC1_Send_Byte(0x78);
        IIC1_Wait_Ack();
	IIC1_Send_Byte(0x40);			//write data
        IIC1_Wait_Ack();
	IIC1_Send_Byte(IIC_Data);
        IIC1_Wait_Ack();
	IIC1_Stop();
}
/*********************OLEDд����************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC1_Start();
	IIC1_Send_Byte(0x78);            //Slave address,SA0=0
        IIC1_Wait_Ack();
	IIC1_Send_Byte(0x00);			//write command
        IIC1_Wait_Ack();
	IIC1_Send_Byte(IIC_Command);
        IIC1_Wait_Ack();
	IIC1_Stop();
}
/*********************OLED ��������************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLEDȫ��************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED��λ************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED��ʼ��************************************/
void OLED_Init(void)
{
    IIC1_Init();
	delay_0(500);//��ʼ��֮ǰ����ʱ����Ҫ��
	OLED_WrCmd(0xae);//--turn off oled panel

	OLED_WrCmd(0x40);//---set low column address
	OLED_WrCmd(0xB0);//---set high column address

	OLED_WrCmd(0xC8);//-not offset

	OLED_WrCmd(0x81);//���öԱȶ�
	OLED_WrCmd(0xff);

	OLED_WrCmd(0xa1);//���ض�������

	OLED_WrCmd(0xa6);//
	
	OLED_WrCmd(0xa8);//��������·��
	OLED_WrCmd(0x1f);
	
	OLED_WrCmd(0xd3);
	OLED_WrCmd(0x00);
	
	OLED_WrCmd(0xd5);
	OLED_WrCmd(0xf0);
	
	OLED_WrCmd(0xd9);
	OLED_WrCmd(0x22);
	
	OLED_WrCmd(0xda);
	OLED_WrCmd(0x02);
	
	OLED_WrCmd(0xdb);
	OLED_WrCmd(0x49);
	
	OLED_WrCmd(0x8d);
	OLED_WrCmd(0x14);
	 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //��ʼ����
	OLED_Set_Pos(0,0);
} 
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}

void OLED_Showchar(unsigned char x,unsigned char y,unsigned char ch)
{
	unsigned char c=0,i=0;
	c =ch-32;
	if(x>126){x=0;y++;}
	OLED_Set_Pos(x,y);
	for(i=0;i<6;i++)
	OLED_WrDat(F6x8[c][i]);
}

//m^n����
unsigned int  mypow(unsigned int m,unsigned int n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}

void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len)
{
  unsigned char t,temp,size1=6;
  unsigned char enshow=0;
        for(t=0;t<len;t++)
	    {
		    temp=(num/mypow(10,len-t-1))%10;
		    if(enshow==0&&t<(len-1))
		    {
			    if(temp==0)
			    {
				    OLED_Showchar(x+size1*t,y,'0');
				    continue;
			    }else enshow=1; 
            }
		    OLED_Showchar(x+size1*t,y,temp+'0'); 
        }
}
//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); N:������codetab.h�е�����
// Description    : ��ʾcodetab.h�еĺ���,16*16����
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
}

