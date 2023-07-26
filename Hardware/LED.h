#ifndef __LED_H__
#define __LED_H__

#define LEDON GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);  //led 亮
#define LEDOFF GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET); //led 灭

void LED_Init(void);

#endif
