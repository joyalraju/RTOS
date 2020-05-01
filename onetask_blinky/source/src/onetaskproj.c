#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#define red_led 0U
#define green_led 1U
#define blue_led 2U
#define GPIO_INTERRUPT_PIN_A   MYBUTTON_A_BIT_NUM	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PIN_B   MYBUTTON_B_BIT_NUM	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PORT    GPIOINT_PORT2
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler	/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_Buttons_Init();
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);

	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIO_INTERRUPT_PORT,
				(1 << GPIO_INTERRUPT_PIN_A) | (1 << GPIO_INTERRUPT_PIN_B));

		/* Enable interrupt in the NVIC */
		NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
		NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);
}
/* Task function */
static void vLEDTask1(void *pvParameters)
{
	portTickType xLastWakeTime;
	int *color = (int*) pvParameters;
	int a=1000;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT,
					(1 << GPIO_INTERRUPT_PIN_A));
		if (Board_MyButtons_Test(ButtonA))
				a=a+500;
		Board_LED_Set(color, 0);
		vTaskDelayUntil( &xLastWakeTime, a);
		Board_LED_Set(color, 1);
		vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}
int main(void)
{
	prvSetupHardware();
	while (1)
	{
		xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
				configMINIMAL_STACK_SIZE, red_led, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);
		xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed2",
				configMINIMAL_STACK_SIZE, green_led, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);
		xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed3",
				configMINIMAL_STACK_SIZE, blue_led, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);
		/* Start the scheduler */
		vTaskStartScheduler();
	}
	return 1;
}
