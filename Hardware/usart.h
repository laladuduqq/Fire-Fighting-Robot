
#include "stm32f10x.h"                  // Device header

#ifndef __USART_H__
#define __USART_H__

#define RXD2_BUF_SIZE   200
	  	
extern u8 RXD2BUF[RXD2_BUF_SIZE];//接收缓冲,最大USART_REC_LEN个字节.
	

void USART2_Init(u32 baudrate);

#endif
