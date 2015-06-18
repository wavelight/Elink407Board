#include "buzzer.h"
#include "stm32f4xx.h"


void init_buzzer(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
	/* Enable the GPIO_BEEP Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);//����
	
}

void buzzer_off(void)
{
	
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);//����
	
}

void buzzer_on(void)
{
	
		GPIO_SetBits(GPIOC,GPIO_Pin_0);//��
	
}
