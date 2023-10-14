#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"

#ifndef __HCSR04_H__
#define __HCSR04_H__
void HCSR04_init(void);
void HC_SR04_start(void);
u32 GetEchoTimer(void);
float HCSR04GetLength(void);
#endif

