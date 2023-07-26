#ifndef __LED_H__
#define __LED_H__

#define LEDSet GPIO_WriteBit(GPIOC,GPIO_Pin_13,0);  //led 亮
#define LEDReset GPIO_WriteBit(GPIOC,GPIO_Pin_13,1); //led 灭

void LED_Init(void);

#endif
