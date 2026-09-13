#include "stm32f10x.h"                  // Device header

/*
RXD-------PA2  蓝牙
TXD-------PA3 
*/

#define RXD GPIO_Pin_2
#define TXD GPIO_Pin_3

void Serial_Init()
{
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	   GPIO_InitTypeDef GPIO_InitStructure;
	   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	   GPIO_InitStructure.GPIO_Pin=RXD; 
	   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	   GPIO_Init(GPIOA,&GPIO_InitStructure);
		  
	   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	   GPIO_InitStructure.GPIO_Pin=TXD; 
	   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	   GPIO_Init(GPIOA,&GPIO_InitStructure);
	   
	   USART_InitTypeDef USART_InitStructure;
	   USART_InitStructure.USART_BaudRate=9600;
	   USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	   USART_InitStructure.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	   USART_InitStructure.USART_Parity=USART_Parity_No;
	   USART_InitStructure.USART_StopBits=USART_StopBits_1;
	   USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	   USART_Init(USART2,&USART_InitStructure);
       
	   USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	   
	   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	             //选择NVIC中断优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;                        
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;                //选择要启用或禁用的中断通道 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                //是否启用或禁用NVIC_IRQChannel赋值的中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;      //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;             //设置响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
       USART_Cmd(USART2,ENABLE);
}
	


