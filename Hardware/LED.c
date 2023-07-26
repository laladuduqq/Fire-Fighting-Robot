#include "stm32f10x.h"
#include "LED.h"

void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //启能GPIOC时钟

    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitTypeDefStrue);  //配置GPIOC_PIN_13 推挽输出

    GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET); //默认高电平
}
