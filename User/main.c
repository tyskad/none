#include "stm32f10x.h"                  // Device header
#include "Delay.h"  
#include "OLED.h"  
#include "TB6612.h"
#include "Serial.h"
#include "HCSR04.h"
#include "SG90.h"
#include "TCRT5000.h"

/*
PWM1------PA1 马达
PWM2------PA6

AIN1------PB10  tb6612 定时器2和定时器3
AIN2------PB1

BIN1------PA4
BIN2------PA5

RXD-------PA2  蓝牙
TXD-------PA3 

Tring-----PA9  超声波     定时器1
Echo------PA10   

PWM0------PB6  舵机    定时器4

TCRT1-----PB12   红外循迹
TCRT2-----PB13
TCRT3-----PB14
TCRT4-----PB15  
*/

uint8_t BlueData,MODE=0,Speed=0;
uint32_t Distan_Right,Distan_Left,Distan_Mid;

uint8_t Array,Last_Array;
uint8_t TCRT_Data[5];

int main()
{
	TB6612_Init();
    Serial_Init();
    SG90_Init();
	HCSR04_Init();	 
	TCRT5000_Init(); 
	
	
    Stop();
	SG90_SetAngle(90);

         while(1)
         {
		   switch (MODE)
		   {
			   case 0: Stop(); while(MODE == 0){;} break;//模式0，蓝牙遥控
		   			   
			   case 1:  while(MODE == 1)                 //模式1，自动避障
			            {
						  SetForward(50);
			              Distan_Mid=HCSR04_Measuring_mm();
			              Delay_ms(200);
							
            			  if( Distan_Mid<300)
						  {
						      Stop();
							  SG90_SetAngle(180);
							  Delay_s(2);
							  Distan_Left=HCSR04_Measuring_mm();
							  
							  SG90_SetAngle(0);
							  Delay_s(2);
							  Distan_Right=HCSR04_Measuring_mm();
									
                              SG90_SetAngle(90);
							  Delay_s(1);
							  
							  if(Distan_Left>Distan_Right)
							  {
							    TurnLeft(80);
								Delay_s(2);								
							  }
							  else
							  {
							    TurnRight(80);						  
								Delay_s(2);
							  }
						  }
						  
 						}
			     break;	   
                
              case 2:  while(MODE == 2)              //模式2自动巡迹
			           {
					    TCRT_Data[1]=TCRT1_Signed();
					    TCRT_Data[2]=TCRT2_Signed();
					    TCRT_Data[3]=TCRT3_Signed();
					    TCRT_Data[4]=TCRT4_Signed();
					    
						if(!TCRT_Data[1] && TCRT_Data[2] && TCRT_Data[3] && !TCRT_Data[4])  //直行//黑色Do高电平
						{
						   SetForward(70);
						   Array=3;
						}
						
						 else if(!TCRT_Data[1] && !TCRT_Data[2] && !TCRT_Data[3] && !TCRT_Data[4])  //中弯
						{
						   if(Last_Array==2)     {TurnLeft(70);Array=1;}	     //左中弯    					   						     						   
						   else if(Last_Array==4){TurnRight(70);Array=5;}  //右中弯	
				
						   
						}
						else if(TCRT_Data[1] && !TCRT_Data[2] && !TCRT_Data[3] && !TCRT_Data[4])  //左大弯
						{
						   TurnLeft(80);
						   Array=0;
						}
						
                      
						else if(!TCRT_Data[1] && TCRT_Data[2] && !TCRT_Data[3] && !TCRT_Data[4])  //左小弯
						{
						   TurnLeft(60);
						   Array=2;
						}
						
						else if(!TCRT_Data[1] && !TCRT_Data[2] && TCRT_Data[3] && !TCRT_Data[4])  //右小弯
						{
						   TurnRight(60);
						   Array=4;
						}
						
						else if(!TCRT_Data[1] && !TCRT_Data[2] && !TCRT_Data[3] && TCRT_Data[4])  //右大弯
						{
						   TurnRight(80);
						   Array=6;
						}
						
                       	else if(!TCRT_Data[1] && TCRT_Data[2] && TCRT_Data[3] && TCRT_Data[4])  //右直角
						{
						   TurnRight(100);
						}
						
					    else if(TCRT_Data[1] && TCRT_Data[2] && TCRT_Data[3] && !TCRT_Data[4])  //左直角
						{ 
						   TurnLeft(100);
						}
						
						else if(TCRT_Data[1] && TCRT_Data[2] && TCRT_Data[3] && TCRT_Data[4])  //终点
						{ 
						  Stop();
						}

						Last_Array=Array;
						Delay_ms(30);
					   }	
                break;
					   
		   }                	       
	  }
}
		 

void USART2_IRQHandler()
{
   if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
   {
	  BlueData=USART_ReceiveData(USART2);
	   switch (BlueData)
		   {
			   case 0x11:  SetForward(60+Speed*20);  break;
			   case 0x12:  SetBack();                break;	
			   case 0x13:  TurnLeft(80);             break;
			   case 0x14:  TurnRight(80);            break;
			   case 0x15:  Stop();                   break;		   
			   case 0x18:  Speed++;Speed%=3;         break;		

				 
				 
			   case 0x20:  MODE=0; break;
			   case 0x21:  MODE=1; break;
			   case 0x22:  MODE=2; break;
		   } 
		   
	  USART_ClearITPendingBit(USART2,USART_IT_RXNE);
   }
   
}

