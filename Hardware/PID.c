#include "PID.h"
// 初始化PWM参数
void PWM_Init(PWM *pwm, float Kp, float Ki, float Kd, float setpoint) {
    pwm->Kp = Kp;
    pwm->Ki = Ki;
    pwm->Kd = Kd;
    pwm->setpoint = setpoint;
    pwm->integral = 0;
    pwm->pre_error = 0;
}

// 更新PWM参数
void PWM_Update(PWM *pwm, float current_value) {
    float error = pwm->setpoint - current_value;
    pwm->integral += error;
    float derivative = error - pwm->pre_error;
    float output = pwm->Kp * error + pwm->Ki * pwm->integral + pwm->Kd * derivative;
    pwm->pre_error = error;

    // 根据输出值设置PWM占空比
    // ...
}