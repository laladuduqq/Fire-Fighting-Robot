#include "usart.h"
#include "stm32f10x.h"

u8 USART_RxData;  //接收rx的数据
u8 USART_RxFlag;  //接收标志位
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

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
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//USART1 每次接收到一个字节,触发中断
}

void USART2_IRQHandler(void){
    
    u8 Res;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		if((USART_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 
    USART_ClearITPendingBit(USART2,USART_IT_RXNE); //清除中断
}



