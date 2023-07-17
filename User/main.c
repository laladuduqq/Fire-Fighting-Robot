#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "KEY.h"

int main(void){
	LED_Init();
	delay_init(); 
	MOTOR_Init(); //电机初始化
	USART1_Init(115200);  //USART1 波特率 115200
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	u8 key=0;
	u8 Speed=0;
	while(1){
		LEDSet;
		key=KEY_Scan(0);
		if(key==KEY0_PRESS){Speed+=10;USART_SendData(USART1,Speed);LEDReset;if(Speed>100){Speed=0;}}
		MOTOR_Forward(Speed*10);
		
		
	}
}
