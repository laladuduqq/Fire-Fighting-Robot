#include "stm32f10x.h"

#ifndef __PID_H__
#define __PID_H__

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float setpoint;
    float integral;
    float pre_error;
} PWM;



#endif