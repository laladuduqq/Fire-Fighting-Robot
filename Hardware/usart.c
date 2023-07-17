#include "usart.h"
#include "stm32f10x.h"

void USART1_Init(u32 Baudrate){    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //串口时钟使能 usart——》PA.9 PA.10 使能

    USART_DeInit(USART1);//串口复位

    GPIO_InitTypeDef GPIO_InitTypeDefStrue;

    //USART_TX 配置
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitTypeDefStrue.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitTypeDefStrue.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitTypeDefStrue);

    //USART_RX 配置
    GPIO_InitTypeDefStrue.GPIO_Pin=GPIO_Pin_10;
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
    USART_Init(USART1,&USART_InitTypeDefStrue);  //初始化串口1

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器
    
    //usart使能
    USART_Cmd(USART1,ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//USART1 每次接收到一个字节,触发中断
}

void USART1_IRQHandler(void){
    extern u8 Res;
    
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
        Res =USART_ReceiveData(USART1);	//读取接收到的数据
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE); //清除中断
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //等待数据发送完成,防止缓冲区溢出
}


