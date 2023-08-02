#include "stm32f10x.h"                  // Device header


#ifndef __ENCODER_H__
#define __ENCODER_H__

void Encoder_Init(void);
int16_t Encoder_GetTIM3(void);
int16_t Encoder_GetTIM1(void);




#endif

