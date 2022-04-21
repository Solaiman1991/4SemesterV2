 /*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

//library filer
#include <ATMEGA_FreeRTOS.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <semphr.h>
#include <task.h>
#include <serial.h>

//include drivers
#include "hih8120.h"
#include "serial.h"
#include "TerrariumFiles/terrarium_Data.h"
#include "stdio_driver.h"


//header filer for de task vi opretter
#include "TerrariumFiles/temp_sensor.h"

//definere vores min og maks ( vha. FreeRTOS)
#define TEMP_TASK_PRIORITY (configMAX_PRIORITIES - 3)


//task setup
TaskHandle_t tempSensorHandle = NULL;


int main() {
	//Hej Solaiman
	
	//vi starter med at sætte alle variablerne til 0
	//terrariumdata.humidity = 0;
	terrariumdata.temperature = 0;
	
	
	// for at printe ud skal dette her med ( header filen "stdio_driver.h" skal includes
	stdio_initialise(ser_USART0);
	
	//opretter de Task vi skal lave ( vha. FreeRTOS)
	xTaskCreate(tempSensorTask, "Temperature measurement", configMINIMAL_STACK_SIZE, NULL, TEMP_TASK_PRIORITY, &tempSensorHandle);

	// Innitalisere semaphoren
	semaphore = xSemaphoreCreateMutex();
	
	// initialalisere temp/fugt måleren
	if(HIH8120_OK !=  hih8120_initialise()) {
		printf("Failed to initialize temperature sensor\n");
		return 1;
	}
	
// der må ikke køres kode, når scheduleren er eksiveret
	vTaskStartScheduler();
	

}


