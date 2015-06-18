#include "timer.h"
#include "stdio.h"

//通用定时器3中断初始化 
//arr：自动重装值。  psc：时钟预分频数 
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us. 
//Ft=定时器工作频率,单位:Mhz 
void timer_init(u16 arr,u16 psc) 
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //①使能TIM3时钟 
   
	TIM_TimeBaseInitStructure.TIM_Period = arr;  //自动重装载值 
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;    //定时器分频 
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  
   
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//  ②初始化定时器TIM3 
   
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //③允许定时器3更新中断 
   
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //响应优先级3 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);//  ④初始化NVIC  
	TIM_Cmd(TIM3,ENABLE); //⑤使能定时器3  
}

void TIM3_IRQHandler(void) 
{ 
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断 
	{ 
		printf("timer out !\r\n");
	} 
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);    //清除中断标志位 
}
