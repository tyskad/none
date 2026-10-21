#ifndef __APP_CAR_H
#define __APP_CAR_H

#include "stm32f10x.h"                  
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "MPU6050.h"
#include "Motor.h"
#include "Encoder.h"
#include "BlueSerial.h"
#include "PID.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

void App_Car_GetData(void);

void App_Car_Display(void);

void App_Car_PID(void);

void App_Car_Ctrl(void);

#endif
