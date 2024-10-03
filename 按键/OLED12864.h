/************************************************************************************
*
* Function List:
* 1. void OLED_WrDat(unsigned char dat) -- ��OLED��д����
* 2. void OLED_WrCmd(unsigned char cmd) -- ��OLED��д����
* 3. void OLED_Set_Pos(unsigned char x, unsigned char y) -- ������ʾ����
* 4. void OLED_Fill(unsigned char bmp_dat) -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
* 5. void OLED_CLS(void) -- ��λ/����
* 6. void OLED_Init(void) -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
* 7. void OLED_P6x8Str(unsigned char x, y,unsigned char ch[]) -- 6x8������������ʾASCII�����С���У���̫����
* 8. void OLED_P8x16Str(unsigned char x, y,unsigned char ch[]) -- 8x16������������ʾASCII�룬�ǳ�����
* 9.void OLED_P16x16Ch(unsigned char x, y, N) -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
* 0.void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ��128x64���ص�BMPλͼ��ȡ�����������ֱ�Ȼ���Ƶ�codetab�У��˺������ü���
*
* History: none;
*
*************************************************************************************/


#ifndef __OLED12864_H
#define __OLED12864_H
#include "myiic.h"
// ------------------------------------------------------------
// IO��ģ��I2Cͨ��
// SCL
// SDA
// ------------------------------------------------------------

#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

void OLED_WrDat(unsigned char IIC_Data);
void OLED_WrCmd(unsigned char IIC_Command);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char bmp_dat);
void OLED_CLS(void);
void OLED_Init(void);
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Showchar(unsigned char x,unsigned char y,unsigned char ch);
unsigned int  mypow(unsigned int m,unsigned int n);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int number,unsigned char len);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

#endif

