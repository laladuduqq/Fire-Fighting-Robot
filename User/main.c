#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "KEY.h"
#include "OLED.h"
#include "adc.h"
#include "encoder.h"


int main(void){
	u8 t,len,i;
	u8 temp[8]={'0'};
	u16 adcx1,adcx2,adcx3;
	LED_Init();
	OLED_Init();
	delay_init(); 
	MOTOR_Init(); //电机初始化
	USART2_Init(115200);  //USART2 波特率 115200
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Encoder_Init();
	Adc_Init();
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
				for(i=0;i<8;i++){temp[i]=USART_RX_BUF[i];}
				USART_SendData(USART2, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
				OLED_Clear();
				//OLED_ShowString(1, 1, "UARTRX:");
				//OLED_ShowString(1, 1, temp);
				//OLED_ShowString(2, 1, USART_RX_BUF);
			}
			USART_RX_STA=0;
		}
		//MOTO_Control(temp);
		adcx1=Get_Adc_Average(ADC_Channel_0,10);
		adcx2=Get_Adc_Average(ADC_Channel_1,10);
		adcx3=Get_Adc_Average(ADC_Channel_4,10);
		OLED_ShowNum(1,1,adcx1,4);
		OLED_ShowNum(2,1,adcx2,4);
		OLED_ShowNum(3,1,adcx3,4);
		OLED_ShowString(4, 1, "ADCtest");
		
		
	}
}
