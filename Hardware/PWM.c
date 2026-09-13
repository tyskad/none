#include "stm32f10x.h"                  // Device header
/*
PWM1-----PA1
PWM2-----PA6
*/
#define PWM1 GPIO_Pin_1
#define PWM2 GPIO_Pin_6

void PWM1_Init()
{
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Pin=PWM1;
	  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	  
	  TIM_InternalClockConfig(TIM2);
	
	  TIM_TimeBaseInitTypeDef TIM2_InitStructure;
	  TIM2_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM2_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	  TIM2_InitStructure.TIM_Period=100-1;
	  TIM2_InitStructure.TIM_Prescaler=720-1;           //100HZ
	  TIM2_InitStructure.TIM_RepetitionCounter=0;      //从0开始向上计数到9999
	  TIM_TimeBaseInit(TIM2,&TIM2_InitStructure);
	
	  TIM_Cmd(TIM2,ENABLE);
	
	  TIM_OCInitTypeDef TIMOC2_InitStructure;
	  TIM_OCStructInit(&TIMOC2_InitStructure);	 
	  TIMOC2_InitStructure.TIM_OCMode=TIM_OCMode_PWM1;	  	  
	  TIMOC2_InitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; 
	  TIMOC2_InitStructure.TIM_OutputState=TIM_OutputState_Enable;
	  TIMOC2_InitStructure.TIM_Pulse=0;  
	  TIM_OC2Init(TIM2,&TIMOC2_InitStructure);
}

void PWM2_Init()
{
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Pin=PWM2;
	  GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	  
	  TIM_InternalClockConfig(TIM3);
	
	  TIM_TimeBaseInitTypeDef TIM3_InitStructure;
	  TIM3_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM3_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	  TIM3_InitStructure.TIM_Period=100-1;
	  TIM3_InitStructure.TIM_Prescaler=720-1;           //100HZ
	  TIM3_InitStructure.TIM_RepetitionCounter=0;      //从0开始向上计数到9999
	  TIM_TimeBaseInit(TIM3,&TIM3_InitStructure);
	
	  TIM_Cmd(TIM3,ENABLE);
	
	  TIM_OCInitTypeDef TIMOC1_InitStructure;
	  TIM_OCStructInit(&TIMOC1_InitStructure);	 
	  TIMOC1_InitStructure.TIM_OCMode=TIM_OCMode_PWM1;	  	  
	  TIMOC1_InitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; 
	  TIMOC1_InitStructure.TIM_OutputState=TIM_OutputState_Enable;
	  TIMOC1_InitStructure.TIM_Pulse=0;  
	  TIM_OC1Init(TIM3,&TIMOC1_InitStructure);
}
