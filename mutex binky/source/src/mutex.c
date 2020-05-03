#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
static void prvSetupHardware(void) //board setting
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);
}
xSemaphoreHandle xMutex;
portTickType xLastWakeTime;
static void vLEDTask1(void *pvParameters) //red led task
{
	while (1)
	{
		xLastWakeTime = xTaskGetTickCount();
		xSemaphoreTake(xMutex, portMAX_DELAY); //Accepting Mutex
		Board_LED_Set(0, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(0, 1);
		xSemaphoreGive(xMutex);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}
static void vLEDTask2(void *pvParameters) //green led task
{
	vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	while (1)
	{
		xLastWakeTime = xTaskGetTickCount();
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Board_LED_Set(1, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(1, 1);
		xSemaphoreGive(xMutex);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}
static void vLEDTask3(void *pvParameters) //blue led task
{
	vTaskDelay(3 * configTICK_RATE_HZ);
	while (1)
	{
		xLastWakeTime = xTaskGetTickCount();
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Board_LED_Set(2, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(2, 1);
		xSemaphoreGive(xMutex);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}
int main(void)
{
	prvSetupHardware();
	xMutex = xSemaphoreCreateMutex(); //create mutex
	xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	xTaskCreate(vLEDTask3, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	/* Start the scheduler */
	vTaskStartScheduler();
	return 1;
}

