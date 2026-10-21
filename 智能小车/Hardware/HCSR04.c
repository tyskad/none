#include "stm32f10x.h"                  // Device header
#include "Delay.h" 

#define Tring  GPIO_Pin_9
#define Echo   GPIO_Pin_10

void HCSR04_Init()
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	 
	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin=Tring; 
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	 GPIO_InitStructure.GPIO_Pin=Echo; 
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	   
	  TIM_InternalClockConfig(TIM1);
	
	  TIM_TimeBaseInitTypeDef TIM1_InitStructure;
	  TIM1_InitStructure.TIM_ClockDivision=0;
	  TIM1_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	  TIM1_InitStructure.TIM_Period=10-1;
	  TIM1_InitStructure.TIM_Prescaler=72-1;           //周期10us
	  TIM1_InitStructure.TIM_RepetitionCounter=0;      
	  TIM_TimeBaseInit(TIM1,&TIM1_InitStructure);
		  
	  TIM_ClearFlag(TIM1,TIM_FLAG_Update);
	  TIM_ITConfig(TIM1,TIM_IT_Update | TIM_IT_Trigger,ENABLE);
	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef TIM1_ITStructure;
	TIM1_ITStructure.NVIC_IRQChannel=TIM1_UP_IRQn;
	TIM1_ITStructure.NVIC_IRQChannelCmd=ENABLE;
	TIM1_ITStructure.NVIC_IRQChannelPreemptionPriority=0;
	TIM1_ITStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&TIM1_ITStructure);
	  
	  TIM_Cmd(TIM1,ENABLE);
	  
}

uint64_t Time=0,TimeEnd=0;

uint16_t HCSR04_Measuring_mm()
{
	uint32_t Distance,Distance_mm=0;
	
    GPIO_WriteBit(GPIOA,Tring,Bit_SET);   
    Delay_us(15);
    GPIO_WriteBit(GPIOA,Tring,Bit_RESET); 
  
	while(GPIO_ReadInputDataBit(GPIOA,Echo) == 0);
    Time=0;
    while(GPIO_ReadInputDataBit(GPIOA,Echo) == 1);
    	
    TimeEnd=Time;
	if(TimeEnd/100 <38 )
	{
	 Distance=(340*TimeEnd)/2;	
	Distance_mm=Distance/100;
	}
   
	return Distance_mm;
}

void TIM1_UP_IRQHandler()                              //每10us进入一次中断
{
  if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)
  {
     Time++;
     TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }

}
