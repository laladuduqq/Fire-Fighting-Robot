#include "stm32f10x.h"

#ifndef __DMA_H__
#define __DMA_H__




void MyDMA_Config(DMA_Channel_TypeDef * channel, u32 perBaseAddr, u32 memBaseAddr, u16 memSize, u8 perDir, u16 priority);
void MyDMA_Start_Channel_Transfer(DMA_Channel_TypeDef * channel, u16 lenDat);

#endif
