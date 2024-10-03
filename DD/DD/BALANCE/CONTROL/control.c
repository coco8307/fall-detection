#include "control.h"	
#include "filter.h"	

u8 Flag_Target;

/**************************************************************************
函数功能：
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 if(PBin(5)==0)		
	{   
		  EXTI->PR=1<<5;                                                      //清除LINE5上的中断标志位   
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
			 }
		  if(Flag_Target==1)                                                  //5ms读取一次陀螺仪和加速度计的值，更高的采样频率可以改善卡尔曼滤波和互补滤波的效果
			{
				Get_Angle(Way_Angle);                                               //===更新姿态	
				return 0;	                                               
			}                                                                   //10ms控制一次，为了保证M法测速的时间基准，首先读取编码器数据
	  	Get_Angle(Way_Angle);                                               //===更新姿态		          
	}       	
	 return 0;	  
} 

void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(50); 
	if(tmp==1)Flag_Stop=!Flag_Stop;
}

/**************************************************************************
函数功能：获取角度 
入口参数：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/
void Get_Angle(u8 way)
{ 
	float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	Read_DMP();                      //===读取加速度、角速度、倾角
	Angle_Balance=Pitch;            //===更新平衡倾角
	Angle_Balance1=Roll;
	Gyro_Balance=gyro[1];            //===更新平衡角速度
	Gyro_Turn=gyro[2];               //===更新转向角速度
	Acceleration_Z=accel[2];         //===更新Z轴加速度计		

}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


