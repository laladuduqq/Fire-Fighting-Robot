#ifndef __SG90_H__
#define __SG90_H__

#include "stm32f10x.h"                  // Device header
#include "HCSR04.h"
#include "OLED.h"
#include "motor.h"
void sg90_init(void);
void avoid_control(void);


#endif