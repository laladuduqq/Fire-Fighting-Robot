#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "KEY.h"
#include "OLED.h"
#include "adc.h"
#include "encoder.h"
#include "linewalk.h"
#include "dma.h"
#include "string.h"


int main(void){
	u16 adcx1,adcx2,adcx3;
	extern u8 RXD2BUF[RXD2_BUF_SIZE];
	extern int flag;
	LED_Init();
	OLED_Init();
	delay_init(); 
	MOTOR_Init(); //电机初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyDMA_Config(DMA1_Channel6,(uint32_t)(&USART2->DR),(uint32_t)RXD2BUF,(uint32_t)RXD2_BUF_SIZE,DMA_DIR_PeripheralSRC,DMA_Priority_Medium);
	USART2_Init(115200);  //USART2 波特率 115200
	Encoder_Init();
	Adc_Init();
	while(1){
		LEDON;
		adcx1=Get_Adc_Average(ADC_Channel_0,2);
		adcx2=Get_Adc_Average(ADC_Channel_1,2);
		adcx3=Get_Adc_Average(ADC_Channel_4,2);
		OLED_ShowNum(1,1,adcx1,4);
		OLED_ShowNum(2,1,adcx2,4);
		OLED_ShowNum(3,1,adcx3,4);
		if(flag==1){
			if(RXD2BUF[0]=='@'){printf("接收到的数据:%s",RXD2BUF);}
			else{printf("数据错误,请重新传输.");}
			OLED_ShowString(4,1,RXD2BUF);
			memset(RXD2BUF,0,200);
			flag=0;
		}
		
	}
}
