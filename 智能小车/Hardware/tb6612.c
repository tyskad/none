#include "stm32f10x.h"                  // Device header
#include "PWM.h" 

/*
AIN1------PB10
AIN2------PB1

BIN1------PA4
BIN2------PA5
*/
#define AIN1 GPIO_Pin_10
#define AIN2 GPIO_Pin_1 
#define BIN1 GPIO_Pin_4 
#define BIN2 GPIO_Pin_5 

void TB6612_Init()
{
	  PWM1_Init();
	  PWM2_Init();
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
      GPIO_InitTypeDef GPIOB_InitStructure;
	  GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIOB_InitStructure.GPIO_Pin=AIN2 | AIN1; 
	  GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIOB_InitStructure);
	
	  GPIO_InitTypeDef GPIOA_InitStructure;
	  GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIOA_InitStructure.GPIO_Pin=BIN1 | BIN2; 
	  GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIOA_InitStructure);
}

void SetForward(uint8_t Duty)
{
	GPIO_WriteBit(GPIOB,AIN1,Bit_RESET);
    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
		
	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
	GPIO_WriteBit(GPIOA,BIN2,Bit_RESET);
	TIM_SetCompare2(TIM2,Duty);
	TIM_SetCompare1(TIM3,Duty);//GPIOA, 控制右侧轮子
}


void SetBack()
{
    GPIO_WriteBit(GPIOB,AIN2,Bit_RESET);
	GPIO_WriteBit(GPIOB,AIN1,Bit_SET);
	
	GPIO_WriteBit(GPIOA,BIN1,Bit_RESET);
	GPIO_WriteBit(GPIOA,BIN2,Bit_SET);
	TIM_SetCompare2(TIM2,80);
	TIM_SetCompare1(TIM3,80);
}


void TurnRight(uint8_t Speed)
{
    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
	GPIO_WriteBit(GPIOB,AIN1,Bit_RESET);
	
	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
	GPIO_WriteBit(GPIOA,BIN2,Bit_SET);
	TIM_SetCompare2(TIM2,Speed);
	TIM_SetCompare1(TIM3,0);
}


void TurnLeft(uint8_t Speed)
{
    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
	GPIO_WriteBit(GPIOB,AIN1,Bit_SET);
	
	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
	GPIO_WriteBit(GPIOA,BIN2,Bit_RESET);
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare1(TIM3,Speed);
}

//void TurnLeft_continue(uint8_t LSpeed,uint8_t RSpeed)
//{
//    GPIO_WriteBit(GPIOB,AIN1,Bit_RESET);
//    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
//		
//	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
//	GPIO_WriteBit(GPIOA,BIN2,Bit_RESET);
//	TIM_SetCompare2(TIM2,RSpeed);
//	TIM_SetCompare1(TIM3,LSpeed);
//}

//void TurnRight_continue(uint8_t LSpeed,uint8_t RSpeed)
//{
//    GPIO_WriteBit(GPIOB,AIN1,Bit_RESET);
//    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
//		
//	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
//	GPIO_WriteBit(GPIOA,BIN2,Bit_RESET);
//	TIM_SetCompare2(TIM2,RSpeed);
//	TIM_SetCompare1(TIM3,LSpeed);
//}

void Stop()
{
    GPIO_WriteBit(GPIOB,AIN2,Bit_SET);
	GPIO_WriteBit(GPIOB,AIN1,Bit_SET);
	
	GPIO_WriteBit(GPIOA,BIN1,Bit_SET);
	GPIO_WriteBit(GPIOA,BIN2,Bit_SET);
	TIM_SetCompare2(TIM2,0);
	TIM_SetCompare1(TIM3,0);
}
