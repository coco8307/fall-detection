#include "control.h"	
#include "filter.h"	

u8 Flag_Target;

/**************************************************************************
�������ܣ�
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 if(PBin(5)==0)		
	{   
		  EXTI->PR=1<<5;                                                      //���LINE5�ϵ��жϱ�־λ   
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //���������ṩ50ms�ľ�׼��ʱ
			 }
		  if(Flag_Target==1)                                                  //5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ�����ߵĲ���Ƶ�ʿ��Ը��ƿ������˲��ͻ����˲���Ч��
			{
				Get_Angle(Way_Angle);                                               //===������̬	
				return 0;	                                               
			}                                                                   //10ms����һ�Σ�Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
	  	Get_Angle(Way_Angle);                                               //===������̬		          
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
�������ܣ���ȡ�Ƕ� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
	float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
	Angle_Balance=Pitch;            //===����ƽ�����
	Angle_Balance1=Roll;
	Gyro_Balance=gyro[1];            //===����ƽ����ٶ�
	Gyro_Turn=gyro[2];               //===����ת����ٶ�
	Acceleration_Z=accel[2];         //===����Z����ٶȼ�		

}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


