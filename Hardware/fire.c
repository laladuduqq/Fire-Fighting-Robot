#include "fire.h"
void fire(void){
    GPIO_InitTypeDef GPIO_InitTypeDefStrue;
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitTypeDefStrue);
}

void fire_state(void){
    u8 i=0,k=0;
    while(k!=5){
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==0){i=i+1;}
        k=k+1;
        delay_ms(100);
    }
    if(i>3){
        printf("发现火源\r\n");
        length=HCSR04GetLength();
        printf("火源距离:%f",length);
    }
}

