#ifndef __LED_H
#define __LED_H
#include "sys.h"
//LED 端口定义
#define LED0 PCout(13) // Pc13
#define LED1 PBout(4)// LED0
#define BEEP PBout(0)// LED1
void LED_Init(void);  //初始化
void Led_Flash(u16 time);
#endif
