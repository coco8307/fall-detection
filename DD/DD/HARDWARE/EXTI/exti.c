#include "exti.h"

/**************************************************************************
函数功能：外部中断初始化
入口参数：无
返回  值：无 
**************************************************************************/
void EXTI_Init(void)  //接入6050中断引脚（PB5）
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	 
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00800000;//PB5上拉输入
  GPIOB->ODR|=1<<5;      //PB5上拉	
	Ex_NVIC_Config(GPIO_B,5,FTIR);		//下降沿触发
	MY_NVIC_Init(1,2,EXTI9_5_IRQn,2);  	//抢占2，子优先级1，组2
}










