#include "sys.h"
#include "OLED12864.h"
#include "stmflash.h"
#include "rtc.h"
#include "delay.h"
#define FLASH_SAVE_ADDR  0X0800C000
u8 Way_Angle=1;                             //获取角度的算法
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开                          
float Angle_Balance,Angle_Balance1,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡角速度 转向角速度
u8 delay_50,delay_flag;  
float Acceleration_Z;                      //Z轴加速度计  
unsigned char Year,Month,Day,Hour,Minute,Second;

int secsec=0;
extern u8 send_flag;
extern u8 USART3_RX_BUF[1],USART3_RX_STA;
char No_dat[16]="\"15977337828\"\r\n\0";
int main(void)
{ 
	u16 i=0,count0=0,see=0;
	u8 t;
	u8 dat[8],KEY0,H_buff[6],buff_01[12];;
	Stm32_Clock_Init(9);            //系统时钟设置
	delay_init(72);                 //延时初始化
	uart_init(72,115200);
	JTAG_Set(JTAG_SWD_DISABLE);     //关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //初始化与 LED 连接的硬件接口
	KEY_Init();                     //按键初始化
	OLED_Init();                    //OLED初始化
	uart_init(72,115200);           //初始化串口1
	uart3_init(36,9600);            //串口3初始化
	IIC_Init();                     //模拟IIC初始化
	MPU6050_initialize();           //MPU6050初始化	
	DMP_Init();                     //初始化DMP     
	                    
	USART2_Init(36,115200);			//串口2初始化
	RTC_Init();
	BEEP=0;
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)No_dat,16);
	if(No_dat[1]!='1')
	{
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)No_dat,11);
		STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)No_dat,16);
	}

	buff_01[0]=No_dat[1];
	buff_01[1]=No_dat[2];
	buff_01[2]=No_dat[3];
	buff_01[3]=No_dat[4];
	buff_01[4]=No_dat[5];
	buff_01[5]=No_dat[6];
	buff_01[6]=No_dat[7];
	buff_01[7]=No_dat[8];
	buff_01[8]=No_dat[9];
	buff_01[9]=No_dat[10];
	buff_01[10]=No_dat[11];

	OLED_ShowCN(0,0,0);		  
	OLED_ShowCN(16,0,1);
	OLED_ShowCN(32,0,2);
	OLED_ShowCN(48,0,3);
	OLED_ShowCN(64,0,4);
	OLED_ShowCN(80,0,5);
	OLED_ShowCN(96,0,6);
	OLED_ShowCN(112,0,7);
	OLED_ShowCN(0,2,8);
	OLED_ShowCN(16,2,9);
	OLED_ShowCN(32,2,10);
	OLED_ShowCN(48,2,11);
	OLED_ShowCN(64,2,12);
	OLED_ShowCN(80,2,13);
	OLED_ShowCN(96,2,14);
	OLED_ShowCN(112,2,15);
	i=10000;
	while(i--)
	{
		delay_us(200);
	}

	OLED_CLS();
//	OLED_ShowStr(0,0,"                  ");
	OLED_ShowStr(0,0,buff_01);
//	OLED_ShowStr(72,0,"  ");
	i=10000;
	LED1=0;
	while(i--)
	{
		delay_us(200);
		if(USART3_RX_STA==1)
		{
			USART3_RX_STA=0;
			KEY0=USART3_RX_BUF[0];
			OLED_Showchar(50,3,KEY0);
		}
		if(KEY0=='A')
		{
			while(1)
			{
				see++;
				if(USART3_RX_STA==1)
				{
					USART3_RX_STA=0;
					KEY0=USART3_RX_BUF[0];
					OLED_Showchar(50,3,KEY0);
					if(KEY0=='D')
					{
						i=9990;
						No_dat[0]='\"';
						No_dat[1]=buff_01[0];
						No_dat[2]=buff_01[1];
						No_dat[3]=buff_01[2];
						No_dat[4]=buff_01[3];
						No_dat[5]=buff_01[4];
						No_dat[6]=buff_01[5];
						No_dat[7]=buff_01[6];
						No_dat[8]=buff_01[7];
						No_dat[9]=buff_01[8];
						No_dat[10]=buff_01[9];
						No_dat[11]=buff_01[10];
						No_dat[12]='\"';
						No_dat[13]='\r';
						No_dat[14]='\n';
						No_dat[15]='\0';
						STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)No_dat,16);
						break;
					}
					if(KEY0=='B')
					{
						count0++;
						if(count0>10)  count0=0;
					}
					if(KEY0<='9')
					{
						buff_01[count0]=KEY0;
					}
				}
				if(count0==0)
				{
					if(see%1000<500)
					{
						OLED_Showchar(0,0,buff_01[0]);
					}
					else 
					{
						OLED_Showchar(0,0,' ');
						OLED_Showchar(60,0,buff_01[10]);
					}
				}
				if(count0==1)
				{
					if(see%1000<500)
					{
						OLED_Showchar(6,0,buff_01[1]);
					}
					else 
					{
						OLED_Showchar(6,0,' ');
						OLED_Showchar(0,0,buff_01[0]);
					}
				}
				if(count0==2)
				{
					if(see%1000<500)
					{
						OLED_Showchar(12,0,buff_01[2]);
					}
					else 
					{
						OLED_Showchar(12,0,' ');
						OLED_Showchar(6,0,buff_01[1]);

					}
				}
				if(count0==3)
				{
					if(see%1000<500)
					{
						OLED_Showchar(18,0,buff_01[3]);
					}
					else 
					{
						OLED_Showchar(18,0,' ');
						OLED_Showchar(12,0,buff_01[2]);
					}
				}
				if(count0==4)
				{
					if(see%1000<500)
					{
						OLED_Showchar(24,0,buff_01[4]);
					}
					else 
					{
						OLED_Showchar(24,0,' ');
						OLED_Showchar(18,0,buff_01[3]);
					}
				}
				if(count0==5)
				{
					if(see%1000<500)
					{
						OLED_Showchar(30,0,buff_01[5]);
					}
					else 
					{
						OLED_Showchar(30,0,' ');
						OLED_Showchar(24,0,buff_01[4]);
					}
				}
				if(count0==6)
				{
					if(see%1000<500)
					{
						OLED_Showchar(36,0,buff_01[6]);
					}
					else 
					{
						OLED_Showchar(36,0,' ');
						OLED_Showchar(30,0,buff_01[5]);
					}
				}
				if(count0==7)
				{
					if(see%1000<500)
					{
						OLED_Showchar(42,0,buff_01[7]);
					}
					else 
					{
						OLED_Showchar(42,0,' ');
						OLED_Showchar(36,0,buff_01[6]);
					}
				}
				if(count0==8)
				{
					if(see%1000<500)
					{
						OLED_Showchar(48,0,buff_01[8]);
					}
					else 
					{
						OLED_Showchar(48,0,' ');
						OLED_Showchar(42,0,buff_01[7]);
					}
				}
				if(count0==9)
				{
					if(see%1000<500)
					{
						OLED_Showchar(54,0,buff_01[9]);
					}
					else 
					{
						OLED_Showchar(54,0,' ');
						OLED_Showchar(48,0,buff_01[8]);
					}
				}
				if(count0==10)
				{
					if(see%1000<500)
					{
						OLED_Showchar(60,0,buff_01[10]);
					}
					else 
					{
						OLED_Showchar(60,0,' ');
						OLED_Showchar(54,0,buff_01[9]);
					}
				}
			}

		}
	}
	OLED_CLS();
	EXTI_Init();
	secsec=30;
	while(1)
	{     
		if(Flag_Show==0)          //使用OLED显示屏
		{
			oled_show();          //===显示读取的MPU6050数据
		}
		else                      
		{
		}	
	    delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //通过MPU6050的INT中断实现的50ms精准延时	
		
		if(t!=calendar.sec)
		{
			LED0=~LED0;
			secsec++;
			if(secsec>50)  secsec=50;
			t=calendar.sec;
			OLED_ShowNum(0,0,calendar.w_year,4);									  
			OLED_ShowNum(30,0,calendar.w_month,2);									  
			OLED_ShowNum(48,0,calendar.w_date,2);	 
			switch(calendar.week)
			{
				case 0:
					OLED_ShowStr(66,1,"Sunday   ");
					break;
				case 1:
					OLED_ShowStr(66,1,"Monday   ");
					break;
				case 2:
					OLED_ShowStr(66,1,"Tuesday  ");
					break;
				case 3:
					OLED_ShowStr(66,1,"Wednesday");
					break;
				case 4:
					OLED_ShowStr(66,1,"Thursday ");
					break;
				case 5:
					OLED_ShowStr(66,1,"Friday   ");
					break;
				case 6:
					OLED_ShowStr(66,1,"Saturday ");
					break;  
			}
			OLED_ShowNum(0,1,calendar.hour,2);									  
			OLED_ShowNum(18,1,calendar.min,2);									  
			OLED_ShowNum(36,1,calendar.sec,2);

//			Year=calendar.w_year-2000;
//			Month=calendar.w_month;
//			Day=calendar.w_date;
//			Hour=calendar.hour;
//			Minute=calendar.min;
//			Second=calendar.sec;


			 OLED_Showchar(24,0,'-');
			 OLED_Showchar(42,0,'-');
			 OLED_Showchar(12,1,':');
			 OLED_Showchar(30,1,':');
		}
		if(USART3_RX_STA==1)
		{
			USART3_RX_STA=0;
			KEY0=USART3_RX_BUF[0];
			OLED_Showchar(50,3,KEY0);
			if(KEY0=='C')  {secsec=30;BEEP=0;LED1=0;send_flag=0;}
		}
		if(USART_RX_STA&0X8000)
		{
			 USART_RX_STA=0;
			 if(USART_RX_BUF[1]=='D')  //
			 {
				H_buff[0]=(USART_RX_BUF[4]-0x30)*10+(USART_RX_BUF[5]-0x30);
				H_buff[1]=(USART_RX_BUF[6]-0x30)*10+(USART_RX_BUF[7]-0x30);
				H_buff[2]=(USART_RX_BUF[8]-0x30)*10+(USART_RX_BUF[9]-0x30);
				H_buff[3]=(USART_RX_BUF[10]-0x30)*10+(USART_RX_BUF[11]-0x30);
				H_buff[4]=(USART_RX_BUF[12]-0x30)*10+(USART_RX_BUF[13]-0x30);
				H_buff[5]=(USART_RX_BUF[14]-0x30)*10+(USART_RX_BUF[15]-0x30);
				RTC_Set(H_buff[0]+2000,H_buff[1],H_buff[2],H_buff[3],H_buff[4],H_buff[5]);
			 }
			 if(USART_RX_BUF[1]=='N') 
			 {
			 	No_dat[1]=USART_RX_BUF[2];
				No_dat[2]=USART_RX_BUF[3];
				No_dat[3]=USART_RX_BUF[4];
				No_dat[4]=USART_RX_BUF[5];
				No_dat[5]=USART_RX_BUF[6];
				No_dat[6]=USART_RX_BUF[7];
				No_dat[7]=USART_RX_BUF[8];
				No_dat[8]=USART_RX_BUF[9];
				No_dat[9]=USART_RX_BUF[10];
				No_dat[10]=USART_RX_BUF[11];
				No_dat[11]=USART_RX_BUF[12];
				STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)No_dat,16);
			 }
		}		
	} 
}
