#include "stm32f10x.h"
#ifndef __MOTOR_H__
#define __MOTOR_H__


void MOTOR_Init(void);
void MOTOR_Forward(u16 speed);
void MOTOR_Back(u16 speed);
void MOTOR_Left(u16 speed);
void MOTOR_Right(u16 speed);
void MOTOR_Stop(void);
void MOTO_Control(char *temp);
void MOTOA_SET(u8 dir,u16 speed);
void MOTOB_SET(u8 dir,u16 speed);

#endif
