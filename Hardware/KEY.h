#include "stm32f10x.h"

#ifndef __KEY_H__
#define __KEY_H__

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY0_PRESS 	1

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
