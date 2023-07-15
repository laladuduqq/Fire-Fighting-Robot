#include "stm32f10x.h"
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTORB_CH1 GPIO_Pin_8;
#define MOTORB_CH2 GPIO_Pin_9;
#define MOTORA_CH1 GPIO_Pin_6;
#define MOTORA_CH2 GPIO_Pin_7;


void MOTOR_Init(void);
void MOTOR_Forward(u16 speed);
void MOTOR_Back(u16 speed);
void MOTOR_Left(u16 speed);
void MOTOR_Right(u16 speed);
void MOTOR_Stop(void);

void MOTOR_Init0(void);
void motorforward(void);
#endif
