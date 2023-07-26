#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "KEY.h"
#include "OLED.h"

int main(void){
	LED_Init();
	OLED_Init();
	//delay_init(); 
	//MOTOR_Init(); //电机初始化
	//USART1_Init(115200);  //USART1 波特率 115200
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OLED_ShowChar(1, 1, 'B');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	while(1){
		LEDReset;
		
		
	}
}
