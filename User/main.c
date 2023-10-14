#include "main.h"

int main(void){
	//u16 t=0;
	u16 adcx1,adcx2,adcx3,length;
	extern u8 RXD2BUF[RXD2_BUF_SIZE];
	extern int flag;
	extern float llength,rlength;
	LED_Init();
	OLED_Init();
	delay_init(); 
	MOTOR_Init(); //电机初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	MyDMA_Config(DMA1_Channel6,(uint32_t)(&USART2->DR),(uint32_t)RXD2BUF,(uint32_t)RXD2_BUF_SIZE,DMA_DIR_PeripheralSRC,DMA_Priority_Medium);
	USART2_Init(115200);  //USART2 波特率 115200
	//Encoder_Init();
	//Adc_Init();
	sg90_init();
	HCSR04_init();
	fire();
	while(1){
		LEDON;
		//t++;
		//adcx1=Get_Adc_Average(ADC_Channel_0,2);
		//adcx2=Get_Adc_Average(ADC_Channel_1,2);
		//adcx3=Get_Adc_Average(ADC_Channel_4,2);
		//OLED_ShowNum(1,1,adcx1,4);
		//OLED_ShowNum(2,1,adcx2,4);
		//OLED_ShowNum(3,1,adcx3,4);
		//OLED_ShowSignedNum(1,1,(u32)Encoder_GetTIM1(),5);
		//OLED_ShowSignedNum(2,1,(u32)Encoder_GetTIM3(),5);
		length=HCSR04GetLength();
		OLED_ShowSignedNum(1,1,length,5);
//		if(t==500){
//		printf("adcx1:%d\r\n",adcx1);
//		printf("adcx2:%d\r\n",adcx2);
//		printf("adcx3:%d\r\n",adcx3);
//		printf("MOTO1:%d\r\n",Encoder_GetTIM3());
//		printf("MOTO2:%d\r\n",Encoder_GetTIM1());
//		t=0;
//		}
		if(flag==1){
			if(RXD2BUF[0]=='@'){printf("接收到的数据:%s\r\n",RXD2BUF);}
			else{printf("数据错误,请重新传输.\r\n");memset(RXD2BUF,0,200);}
			OLED_Clear();
			OLED_ShowString(4,1,RXD2BUF);
			if(RXD2BUF[1]=='1'){MOTO_Control(RXD2BUF);}
			//else if(RXD2BUF[2]=='1'){linewalk(adcx1,adcx2,adcx3);}
			else if(RXD2BUF[5]=='1'){avoid_control();printf("llength:%f\r\n",llength);printf("rlength:%f\r\n",rlength);}
			else if(RXD2BUF[6]=='1'){fire_state();}
			memset(RXD2BUF,0,200);
			flag=0;
		}

		
				
	}
}

/***************************************
通信协议规定:8位作为一个信号
首位:@-->作为起始标志位
第二位:遥控控制位
第三位:巡线控制位
第四位:避障功能控制位
第五位:机械臂使能位
第六位:图像识别使能位
第七位:火灾监控位
第八位:\r\n -->结束标志位
****************************************/
