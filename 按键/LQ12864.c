/************************************************************************************
* Function List:
* 1. void OLED_WrDat(unsigned char dat) -- 向OLED屏写数据
* 2. void OLED_WrCmd(unsigned char cmd) -- 向OLED屏写命令
* 3. void OLED_Set_Pos(unsigned char x, unsigned char y) -- 设置显示坐标
* 4. void OLED_Fill(unsigned char bmp_dat) -- 全屏显示(显示BMP图片时才会用到此功能)
* 5. void OLED_CLS(void) -- 复位/清屏
* 6. void OLED_Init(void) -- OLED屏初始化程序，此函数应在操作屏幕之前最先调用
* 7. void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]) -- 6x8点整，用于显示ASCII码的最小阵列，不太清晰
* 8. void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]) -- 8x16点整，用于显示ASCII码，非常清晰
* 9.void OLED_P16x16Ch(unsigned char x, y, N) -- 16x16点整，用于显示汉字的最小阵列，可设置各种字体、加粗、倾斜、下划线等
* History: none;
*
*************************************************************************************/

#include "OLED12864.h"
#include "codetab.h"

#define abs(x) ((x) > 0 ? (x) : -(x))

// ------------------------------------------------------------
// IO口模拟I2C通信
// SCL
// SDA
// ------------------------------------------------------------
void Delay500ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	i = 57;
	j = 27;
	k = 112;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void delay(int c)   //误差 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=114;b>0;b--);
            //for(a=12;a>0;a--);
}

/*********************OLED写数据************************************/ 
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
/*********************OLED写命令************************************/
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
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
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
/*********************OLED复位************************************/
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
/*********************OLED初始化************************************/
void OLED_Init(void)
{
    IIC1_Init();
	Delay500ms();//初始化之前的延时很重要！
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
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

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
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

void OLED_Showchar(unsigned char x,unsigned char y,unsigned char ch)
{
	unsigned char c=0,i=0;
	c =ch-32;
	if(x>126){x=0;y++;}
	OLED_Set_Pos(x,y);
	for(i=0;i<6;i++)
	OLED_WrDat(F6x8[c][i]);
}

//m^n函数
unsigned int  mypow(unsigned int m,unsigned int n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}

void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len)
{
  unsigned char t,k,temp,size1=6;
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

