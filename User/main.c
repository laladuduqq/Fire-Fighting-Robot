#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
int main(void){
	u16 speed=500;
	LED_Init();
	delay_init();
	MOTOR_Init();
	USART1_Init(115200);
	u16 t=0;
	while(1){
		LEDSet;
		delay_ms(500);
		LEDWrite;
		delay_ms(500);
		MOTOR_Forward(speed);
		delay_ms(1000);
		MOTOR_Stop();
		delay_ms(500);

		MOTOR_Back(speed);
		delay_ms(1000);
		MOTOR_Stop();
		delay_ms(500);

		MOTOR_Left(speed);
		delay_ms(1000);
		MOTOR_Stop();
		delay_ms(500);

		MOTOR_Right(speed);
		delay_ms(1000);
		MOTOR_Stop();
		delay_ms(500);
		
		t++;
		USART_SendData(USART1,t);

	}

}
