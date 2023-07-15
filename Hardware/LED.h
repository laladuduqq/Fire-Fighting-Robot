#ifndef __LED_H__
#define __LED_H__

#define LEDSet GPIO_SetBits(GPIOC,GPIO_Pin_13);  //led 亮
#define LEDWrite GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET); //led 灭

void LED_Init(void);

#endif
