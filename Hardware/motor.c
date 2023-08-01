#include "motor.h"
#include "stm32f10x.h"
#include "delay.h"

void MOTOR_Init(void){  //pwm
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStrue;  
    TIM_TimeBaseInitTypeDefStrue.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitTypeDefStrue.TIM_Period=100-1;  //f=tim_clock/(period+1) -->周期
    TIM_TimeBaseInitTypeDefStrue.TIM_Prescaler=720-1; //设定定时器工作在24MHZ -->定时器所用时钟
    TIM_TimeBaseInitTypeDefStrue.TIM_ClockDivision=0; //不分频
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitTypeDefStrue); //TIM4定时器初始化



    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitTypeDefStrue);  //GPIO_Pin_8|GPIO_Pin_9 初始化，因为用到定时器-》GPIO_Mode_AF_PP。-->TIM4 CH3 CH4
    
    
    TIM_OCInitTypeDef TIM_OCInitTypeDefStrue;
    TIM_OCInitTypeDefStrue.TIM_OCMode=TIM_OCMode_PWM1; //timx_cnt <timx_crrx 时--> 输出有效电平
    TIM_OCInitTypeDefStrue.TIM_OutputState=TIM_OutputState_Enable; //输出比较使能
    TIM_OCInitTypeDefStrue.TIM_Pulse=0;  //默认整个周期为无效电平
    TIM_OCInitTypeDefStrue.TIM_OCPolarity=TIM_OCPolarity_High;  //有效电平输出为高电平
    TIM_OC1Init(TIM4,&TIM_OCInitTypeDefStrue);
    TIM_OC2Init(TIM4,&TIM_OCInitTypeDefStrue);
    TIM_OC3Init(TIM4,&TIM_OCInitTypeDefStrue);
    TIM_OC4Init(TIM4,&TIM_OCInitTypeDefStrue);//TIM3,TIM4 (CH3 CH4) PWM 输出

    TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
    
    TIM_ARRPreloadConfig(TIM4,ENABLE);

    
    TIM_Cmd(TIM4,ENABLE);

    TIM_SetCompare1(TIM4,0);
    TIM_SetCompare2(TIM4,0);
    TIM_SetCompare3(TIM4,0);
    TIM_SetCompare4(TIM4,0);
    
}



void MOTOA_SET(u8 dir,u16 speed){  //dir->方向（0->反向 1->正向）speed->电机转速
    if(speed>100) speed=100;
    if(dir){
       TIM_SetCompare1(TIM4,speed);
       TIM_SetCompare2(TIM4,0);
    }else{
        TIM_SetCompare1(TIM4,0);
       TIM_SetCompare2(TIM4,speed);
    }
}

void MOTOB_SET(u8 dir,u16 speed){  //dir->方向（0->反向 1->正向）speed->电机转速
    if(speed>100) speed=100;
    if(dir){
       TIM_SetCompare3(TIM4,speed);
       TIM_SetCompare4(TIM4,0);
    }else{
        TIM_SetCompare3(TIM4,0);
       TIM_SetCompare4(TIM4,speed);
    }
}

void MOTOR_Forward(u16 speed){
    MOTOA_SET(1,speed);
    MOTOB_SET(1,speed);
}

void MOTOR_Back(u16 speed){
    MOTOA_SET(0,speed);
    MOTOB_SET(0,speed);
}

void MOTOR_Left(u16 speed){
    MOTOA_SET(1,speed);
    MOTOB_SET(0,speed);
}

void MOTOR_Right(u16 speed){
    MOTOA_SET(0,speed);
    MOTOB_SET(1,speed);
}

void MOTOR_Stop(void){
    TIM_SetCompare3(TIM4,0);
    TIM_SetCompare4(TIM4,0);
    TIM_SetCompare1(TIM4,0);
    TIM_SetCompare2(TIM4,0);
}

void MOTO_Control(u8 *temp){
        if(temp[0]=='1' && (u16)temp[1]=='1' && (u16)temp[2]=='1'){MOTOR_Forward(90);}
        else if(temp[0]=='0' && temp[1]=='1' && temp[2]=='1'){MOTOR_Back(60);}
        else if(temp[0]=='1' && temp[1]=='0' && temp[2]=='1'){MOTOR_Left(60);}
        else if(temp[0]=='1' && temp[1]=='1' && temp[2]=='0'){MOTOR_Right(60);}
        else{MOTOR_Stop();}
}

