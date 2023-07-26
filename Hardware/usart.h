
#include "stm32f10x.h"                  // Device header

#ifndef __USART_H__
#define __USART_H__

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记		

void USART1_Init(u32 baudrate);

#endif
