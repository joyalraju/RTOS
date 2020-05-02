#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);
}
portTickType xLastWakeTime;
static void vLEDTask1(void *pvParameters) //red led task
{
	while (1)
	{
		xLastWakeTime = xTaskGetTickCount();
		Board_LED_Set(0, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(0, 1);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}
static void vLEDTask2(void *pvParameters) //green led task
{
	vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	while (1)
	{
		taskENTER_CRITICAL(); //suppressing green led by allowing kernel to run critical task
		xLastWakeTime = xTaskGetTickCount();
		Board_LED_Set(1, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(1, 1);
		taskEXIT_CRITICAL(); //exiting from critical task
		vTaskDelayUntil( &xLastWakeTime, 3500);

	}
}
static void vLEDTask3(void *pvParameters) //blue led task
{
	vTaskDelay(3 * configTICK_RATE_HZ);
	while (1)
	{
		xLastWakeTime = xTaskGetTickCount();
		Board_LED_Set(2, 0);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(2, 1);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}

int main(void)
{
	prvSetupHardware();
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
