#include "App_Task.h"

extern void xPortSysTickHandler(void);
void  SysTick_Handler(void)
{
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
    }
}


int main(void)
{
	OLED_Init();
	MPU6050_Init();
	BlueSerial_Init();
	LED_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	
	App_Task_Init();
	
	while (1)
	{
		
	}
}
