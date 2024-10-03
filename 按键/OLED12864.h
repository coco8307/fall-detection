/************************************************************************************
*
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
* 0.void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- 将128x64像素的BMP位图在取字软件中算出字表，然后复制到codetab中，此函数调用即可
*
* History: none;
*
*************************************************************************************/


#ifndef __OLED12864_H
#define __OLED12864_H
#include "myiic.h"
// ------------------------------------------------------------
// IO口模拟I2C通信
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

