#include "HCSR04.h"

u32 time=0;

void HCSR04_init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStrue;  
    TIM_TimeBaseInitTypeDefStrue.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitTypeDefStrue.TIM_Period=99;  //f=tim_clock/(period+1) -->周期
    TIM_TimeBaseInitTypeDefStrue.TIM_Prescaler=71; //设定定时器工作在72MHZ -->定时器所用时钟
    TIM_TimeBaseInitTypeDefStrue.TIM_ClockDivision=TIM_CKD_DIV1; //不分频
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeDefStrue); //TIM3定时器初始化


    //TRIG 脉冲输出端
    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitTypeDefStrue);  
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);

    //echo 接收端
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitTypeDefStrue);
    GPIO_ResetBits(GPIOB,GPIO_Pin_4);

    
	NVIC_InitTypeDef NVIC_hcsr04init;//定时器中断结构体初始化
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断定时器优先级分组
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能定时器中断
	TIM_Cmd(TIM3,DISABLE);//失能定时器       
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);                                    //清楚TIM的中断标志位 
	   
	//4.配置定时器中断结构体
	NVIC_hcsr04init.NVIC_IRQChannel     =  TIM3_IRQn;//配置通道4
	NVIC_hcsr04init.NVIC_IRQChannelCmd  =  ENABLE;//使能定时器中断
	NVIC_hcsr04init.NVIC_IRQChannelPreemptionPriority  = 1;//抢占优先级为0
	NVIC_hcsr04init.NVIC_IRQChannelSubPriority         = 1;//子优先级为0		 
	NVIC_Init(&NVIC_hcsr04init);//配置中断初始化
}

//发送10us的脉冲触发信号
void HC_SR04_start(void)
{   
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);                           
    delay_us(10);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);                             //给一个10us的高电平用来开启超声波
    delay_us(10);
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);

}

//获取定时器2计数器值
u32 GetEchoTimer(void)
{
   u32 t = 0;
   t = time*1000;                                                           
   t += TIM_GetCounter(TIM3);
   TIM3->CNT = 0;  
   delay_ms(50);
   return t;
}
//定时器3中断
void TIM3_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
       time++;
   }
}

//通过定时器计数器值推算距离
float HCSR04GetLength(void)
{
   u32 t = 0;
   int i = 0;
   float lengthTemp = 0;
   float sum = 0;
   while(i!=5)
   {
      HC_SR04_start();
      while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == 0);      
      TIM_SetCounter(TIM3,0);  //计数清零
      time = 0;
      TIM_Cmd(TIM3,ENABLE);  //使能TIM2定时器
      i = i + 1;
      while( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == 1);
      TIM_Cmd(TIM3,DISABLE); //关闭定时器
      t = GetEchoTimer();
      lengthTemp = ((float)t/58.0);//cm
      sum = lengthTemp + sum ;    
    }
    lengthTemp = sum/5.0;
    return lengthTemp;
}

 





