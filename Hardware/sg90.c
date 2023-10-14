#include "sg90.h"
float llengthtemp,llength,rlengthtemp,rlength;
u8 i=0;
float length;
void sg90_init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);

    
    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitTypeDefStrue);  
    

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStrue;  
    TIM_TimeBaseInitTypeDefStrue.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitTypeDefStrue.TIM_Period=199;  //f=tim_clock/(period+1) -->周期
    TIM_TimeBaseInitTypeDefStrue.TIM_Prescaler=7199; //设定定时器工作在24MHZ -->定时器所用时钟
    TIM_TimeBaseInitTypeDefStrue.TIM_ClockDivision=0; //不分频
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeDefStrue); //TIM2定时器初始化
    
    
    TIM_OCInitTypeDef TIM_OCInitTypeDefStrue;
    TIM_OCInitTypeDefStrue.TIM_OCMode=TIM_OCMode_PWM1; //timx_cnt <timx_crrx 时--> 输出有效电平
    TIM_OCInitTypeDefStrue.TIM_OutputState=TIM_OutputState_Enable; //输出比较使能
    TIM_OCInitTypeDefStrue.TIM_Pulse=0;  //默认整个周期为无效电平
    TIM_OCInitTypeDefStrue.TIM_OCPolarity=TIM_OCNPolarity_Low;  //有效电平输出为高电平
    TIM_OC2Init(TIM2,&TIM_OCInitTypeDefStrue);

    TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
    
    TIM_ARRPreloadConfig(TIM2,ENABLE);

    
    TIM_Cmd(TIM2,ENABLE);

    TIM_SetCompare2(TIM2,15);
}

void avoid_control(void){
			length=HCSR04GetLength();
			delay_ms(500);//等待length稳定
        if(length<100){
            TIM_SetCompare2(TIM2,14);//正向最小转速
            delay_ms(300);
            TIM_SetCompare2(TIM2,15);//速度为0
            while(i!=5){llengthtemp+=length;i=i+1;}
            llength=llengthtemp/5;  //左边距离判断
            i=0;
            TIM_SetCompare2(TIM2,16);//正向最小转速
            delay_ms(550);
            TIM_SetCompare2(TIM2,15);//速度为0
            while(i!=5){rlengthtemp+=length;i=i+1;}
            rlength=rlengthtemp/5;  //右边距离判断
            i=0;
            TIM_SetCompare2(TIM2,14);//正向最小转速
            delay_ms(300);          //回正
            TIM_SetCompare2(TIM2,15);
        }
        OLED_ShowSignedNum(2,1,llength,5);
        OLED_ShowSignedNum(3,1,rlength,5);
        if(llength>rlength){MOTOR_Left(60);}
        else if(rlength>llength){MOTOR_Right(60);}

}
