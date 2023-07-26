#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "KEY.h"
#include "OLED.h"


int main(void){
	u8 t,len;
	LED_Init();
	OLED_Init();
	delay_init(); 
	//MOTOR_Init(); //电机初始化
	USART1_Init(115200);  //USART1 波特率 115200
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//OLED_ShowString(1, 1, "motor test");
	OLED_ShowString(1, 1, "UARTRX:");
	OLED_ShowCHinese(4,1,0);
	OLED_ShowCHinese(4,3,1);
	//OLED_ShowSignedNum(2, 7, -66, 2);
	while(1){
		LEDON;
		delay_ms(500);
		LEDOFF;
		delay_ms(500);
		if(USART_RX_STA&0x8000) //判断接收是否完成
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				OLED_ShowString(2, 1, USART_RX_BUF);
			}
			USART_RX_STA=0;
		}
		
		
		
	}
}
