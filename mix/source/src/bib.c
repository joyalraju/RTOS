#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
xSemaphoreHandle xMutex;
static void prvSetupHardware(void)
{
SystemCoreClockUpdate();
Board_Init();

/* Initial LED0 state is off */
Board_LED_Set(0, true);
Board_LED_Set(1, true);
Board_LED_Set(2, true);

}

/* LED1 toggle thread */
static void task1(void *pvParameters) // for red and green
{
int *led=(int*)pvParameters;
while (1)
{
xSemaphoreTake(xMutex, portMAX_DELAY);
Board_LED_Set(led,false);
vTaskDelay(1000);
Board_LED_Set(led,true);
vTaskDelay(500);
xSemaphoreGive(xMutex);
vTaskDelay(3500);


}
}
static void task2(void *pvParameters) //blue led task
{
	while (1)
	{
		xSemaphoreTake(xMutex, portMAX_DELAY);
		taskENTER_CRITICAL();
		Board_LED_Set(2, false);
		vTaskDelay(1000);
		Board_LED_Set(2, true);

		xSemaphoreGive(xMutex);
		taskEXIT_CRITICAL();
		vTaskDelay(3500);
	}
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief main routine for FreeRTOS blinky example
 * @return Nothing, function should not exit
 */
int main(void)
{
prvSetupHardware();
xMutex = xSemaphoreCreateMutex();
/* LED1 toggle thread */
xTaskCreate(task1, (signed char* ) "vTaskLed1",
configMINIMAL_STACK_SIZE,0, (tskIDLE_PRIORITY + 3UL),
(xTaskHandle *) NULL);

/* LED2 toggle thread */
xTaskCreate(task1, (signed char* ) "vTaskLed2",
configMINIMAL_STACK_SIZE, 1, (tskIDLE_PRIORITY + 2UL),
(xTaskHandle *) NULL);

xTaskCreate(task2, (signed char* ) "vTaskLed3",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

/* Start the scheduler */
vTaskStartScheduler();

/* Should never arrive here */
return 1;
}
