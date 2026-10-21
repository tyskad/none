#include "app_task.h"

TaskHandle_t start_task_handle;
#define START_TASK_STACK 128
#define START_TASK_PRIORITY 1
void App_Task_Start(void *pvParameters);


TaskHandle_t data_task_handle;
#define DATA_TASK_STACK 128
#define DATA_TASK_PRIORITY 3
void App_Task_GetData(void *pvParameters);


TaskHandle_t pid_task_handle;
#define PID_TASK_STACK 128
#define PID_TASK_PRIORITY 3
void App_Task_PID(void *pvParameters);


TaskHandle_t display_task_handle;
#define DISPLAY_TASK_STACK 128
#define DISPLAY_TASK_PRIORITY 2
void App_Task_Display(void *pvParameters);


TaskHandle_t ctrl_task_handle;
#define DISPLAY_TASK_STACK 128
#define CTRL_TASK_PRIORITY 3
void App_Task_Ctrl(void *pvParameters);


void App_Task_Init(void)
{
    xTaskCreate(
        (TaskFunction_t)App_Task_Start,
        (char *)"App_Task_Start",
        (configSTACK_DEPTH_TYPE)START_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)START_TASK_PRIORITY,
        (TaskHandle_t *)&start_task_handle);

    vTaskStartScheduler();
}


void App_Task_Start(void *pvParameters)
{
    taskENTER_CRITICAL();
    xTaskCreate(
        (TaskFunction_t)App_Task_GetData,
        (char *)"App_Task_GetData",
        (configSTACK_DEPTH_TYPE)DATA_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)DATA_TASK_PRIORITY,
        (TaskHandle_t *)&data_task_handle);
    xTaskCreate(
        (TaskFunction_t)App_Task_PID,
        (char *)"App_Task_PID",
        (configSTACK_DEPTH_TYPE)PID_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)PID_TASK_PRIORITY,
        (TaskHandle_t *)&pid_task_handle);
    xTaskCreate(
        (TaskFunction_t)App_Task_Display,
        (char *)"App_Task_Display",
        (configSTACK_DEPTH_TYPE)DISPLAY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)DISPLAY_TASK_PRIORITY,
        (TaskHandle_t *)&display_task_handle);
	xTaskCreate(
        (TaskFunction_t)App_Task_Ctrl,
        (char *)"App_Task_Ctrl",
        (configSTACK_DEPTH_TYPE)DISPLAY_TASK_STACK,
        (void *)NULL,
        (UBaseType_t)CTRL_TASK_PRIORITY,
        (TaskHandle_t *)&ctrl_task_handle);
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();
}

void App_Task_GetData(void *pvParameters)
{
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();

    while(1)
    {
        App_Car_GetData();
        xTaskNotifyGive(pid_task_handle);
        vTaskDelayUntil(&pxPreviousWakeTime,pdMS_TO_TICKS( 10 ));
    }

}


void App_Task_PID(void *pvParameters)
{
    while(1)
    {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        App_Car_PID();
    }
}


void App_Task_Display(void *pvParameters)
{
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();
    while(1)
    {
        App_Car_Display();
        vTaskDelayUntil(&pxPreviousWakeTime,pdMS_TO_TICKS( 50 ));
    }

}


void App_Task_Ctrl(void *pvParameters)
{
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();
    while(1)
    {
        App_Car_Ctrl();
        vTaskDelayUntil(&pxPreviousWakeTime,pdMS_TO_TICKS( 20 ));
    }

}
