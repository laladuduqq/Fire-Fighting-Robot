#include "KEY.h"
#include "stm32f10x.h"
#include "delay.h"

void KEY_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //启能gpioA时钟
    
    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_IPU;//按键低电平有效->上拉输入
    GPIO_Init(GPIOA,&GPIO_InitTypeDefStrue);

}

u8 KEY_Scan(u8 mode)  //1->连按 0->不连按
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRESS;
	}else if(KEY0==1)key_up=1; 	    
 	return 0;// 无按键按下
}
