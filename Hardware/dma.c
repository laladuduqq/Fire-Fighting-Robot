#include "stm32f10x.h"
#include "dma.h"

/*
 * 函数名 : MyDMA_Config
 * 描  述 : DMA配置
 * 输  入 : channel		: 通道
 * 			perBaseAddr : 外设基地址
 * 			memBaseAddr : 存储器基地址
 * 			memSize     : 存储器大小
 * 			perDir		: 外设方向(DMA_DIR_PeripheralDST/DMA_DIR_PeripheralSRC)
 * 			priority	: 优先级(DMA_Priority_VeryHigh/DMA_Priority_High/DMA_Priority_Medium/DMA_Priority_Low)
 * 说  明 : 1. 外设基地址不变，储存器基地址自增长。
 * 			2. 外设和存储器数据宽度字节对齐。
 * 			3. DMA正常模式，不开启存储器到存储器传输。
 */
void MyDMA_Config(DMA_Channel_TypeDef * channel, u32 perBaseAddr, u32 memBaseAddr, u16 memSize, u8 perDir, u16 priority)
{
    DMA_InitTypeDef DMA_InitStructure;


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  					//Enable DMA1 clock

    DMA_DeInit(channel);                                                    //Reset MDA channel
    DMA_InitStructure.DMA_PeripheralBaseAddr = perBaseAddr;					//Peripheral base address
	DMA_InitStructure.DMA_MemoryBaseAddr 	 = memBaseAddr;					//Memory base address
	DMA_InitStructure.DMA_DIR 			     = perDir;						//DMA transmit direction
	DMA_InitStructure.DMA_BufferSize 		 = memSize;						//MDA Channel buffer size
	DMA_InitStructure.DMA_PeripheralInc 	 = DMA_PeripheralInc_Disable;	//Peripheral address incremented 
	DMA_InitStructure.DMA_MemoryInc 		 = DMA_MemoryInc_Enable;		//Memory address incremented 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//Peripheral data width
	DMA_InitStructure.DMA_MemoryDataSize 	 = DMA_MemoryDataSize_Byte;		//Memory data width
	DMA_InitStructure.DMA_Mode 				 = DMA_Mode_Normal;				//DMAy Channe mode
	DMA_InitStructure.DMA_Priority 			 = priority;					//MDA Channel priority
	DMA_InitStructure.DMA_M2M 				 = DMA_M2M_Disable;				//Memory-to-memory transfer
	DMA_Init(channel, &DMA_InitStructure);									//DMA init

	DMA_Cmd(channel, ENABLE);   //Enable DMA channel
}

/**********************************************************************************************************************************************
 * 函数名 : vDMA_Start_Channel_Transfer
 * 描  述 : 开始DMA通道传输
 * 输  入 : channel : 通道
 * 			lenDat  : 数据长度
 * 说  明 : 1. DMA_SetCurrDataCounter()只在DMA失能下有效
 **********************************************************************************************************************************************/
void MyDMA_Start_Channel_Transfer(DMA_Channel_TypeDef * channel, u16 lenDat)
{
	DMA_Cmd(channel, DISABLE);					//Disable DMA channel
	DMA_SetCurrDataCounter(channel, lenDat);	//Set data count
	DMA_Cmd(channel, ENABLE);					//Enable DMA channel
}


