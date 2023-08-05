#include "usart.h"
#include "stm32f10x.h"
#include "stdio.h" //printf函数用-->哪个c文件用printf,就需要导入一次
#include "dma.h"

u8 RXD2BUF[RXD2_BUF_SIZE];//接收缓冲,最大USART_REC_LEN个字节.

//printf打印支持
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 


void USART2_Init(u32 Baudrate){    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口时钟使能 usart——》PA.2 PA.3 使能

    USART_DeInit(USART2);//串口复位

    GPIO_InitTypeDef GPIO_InitTypeDefStrue;

    //USART_TX 配置
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitTypeDefStrue);

    //USART_RX 配置
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitTypeDefStrue);

    //usart配置
    USART_InitTypeDef USART_InitTypeDefStrue;
    USART_InitTypeDefStrue.USART_BaudRate=Baudrate;
    USART_InitTypeDefStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitTypeDefStrue.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
    USART_InitTypeDefStrue.USART_Parity=USART_Parity_No;
    USART_InitTypeDefStrue.USART_StopBits=USART_StopBits_1;
    USART_InitTypeDefStrue.USART_WordLength=USART_WordLength_8b;
    USART_Init(USART2,&USART_InitTypeDefStrue);  //初始化串口1

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
    
    //usart使能
    USART_Cmd(USART2,ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//USART1 每次接收到一个帧数据,触发中断
    USART_ClearFlag(USART2,USART_FLAG_TC|USART_FLAG_IDLE);
    

    //USART2 使能DMA
    USART_DMACmd(USART2, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);	//Enable DMA receive/transmit request	
    
}



u16 txCount = 0;
int flag=0;
void USART2_IRQHandler(void) 
{
	u16 reCount = 0;
  
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	} 


	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)//Idle interrupt set
	{
		// Clear idle interrupt 
		USART1->SR;//Read state register
		USART1->DR;//Read data register 
		USART_GetITStatus(USART2, USART_IT_IDLE);//Get idle interrupt state
		USART_ReceiveData(USART2);//Get USARTx received data

		reCount = DMA_GetCurrDataCounter(DMA1_Channel6);//Get remaining length 
		txCount = RXD2_BUF_SIZE - reCount;//Used length
		printf("Used:%d --> Remain:%d\r\n", txCount, reCount);
		MyDMA_Start_Channel_Transfer(DMA1_Channel6, RXD2_BUF_SIZE);//Start transfer
	}
    flag=1;
} 





