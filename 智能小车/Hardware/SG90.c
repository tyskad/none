#include "stm32f10x.h"                  // Device header

#define PWM0 GPIO_Pin_6

void SG90_Init()
{ 
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Pin=PWM0;
	  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
	  
	  TIM_InternalClockConfig(TIM4);
	
	  TIM_TimeBaseInitTypeDef TIM4_InitStructure;
	  TIM4_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM4_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	  TIM4_InitStructure.TIM_Period=20000-1;
	  TIM4_InitStructure.TIM_Prescaler=72-1;           //50HZ
	  TIM4_InitStructure.TIM_RepetitionCounter=0;      //从0开始向上计数到9999
	  TIM_TimeBaseInit(TIM4,&TIM4_InitStructure);
	
	  TIM_Cmd(TIM4,ENABLE);
	
	  TIM_OCInitTypeDef TIMOC_InitStructure;
	  TIM_OCStructInit(&TIMOC_InitStructure);	 
	  TIMOC_InitStructure.TIM_OCMode=TIM_OCMode_PWM1;	  	  
	  TIMOC_InitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; 
	  TIMOC_InitStructure.TIM_OutputState=TIM_OutputState_Enable;
	  TIMOC_InitStructure.TIM_Pulse=0;  
	  TIM_OC1Init(TIM4,&TIMOC_InitStructure);
}

void SG90_SetAngle(float Angle)	
{	     
    TIM_SetCompare1(TIM4,Angle / 180 * 2000 + 500);          		 
}
