#include "stm32f10x.h"                  // Device header

#define TCRT1 GPIO_Pin_12
#define TCRT2 GPIO_Pin_13
#define TCRT3 GPIO_Pin_14
#define TCRT4 GPIO_Pin_15

void TCRT5000_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=TCRT1 | TCRT2 | TCRT3 | TCRT4; 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);  
}

uint8_t TCRT1_Signed()
{
     return GPIO_ReadInputDataBit(GPIOB,TCRT1);
}

uint8_t TCRT2_Signed()
{
     return GPIO_ReadInputDataBit(GPIOB,TCRT2);
}

uint8_t TCRT3_Signed()
{
     return GPIO_ReadInputDataBit(GPIOB,TCRT3);
}

uint8_t TCRT4_Signed()
{
     return GPIO_ReadInputDataBit(GPIOB,TCRT4);
}
