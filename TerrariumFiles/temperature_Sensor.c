/*
 * temperature_Sensor.c
 *
 * Created: 20-04-2022 13:10:26
 *  Author: Solaiman
 */ 


#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdio_driver.h>
#include "temperature_Sensor.h"
#include "semphr.h"
#include "hih8120.h"
#include "terrarium_Data.h"


void tempSensorTask(void* pvParameters) {
	(void)pvParameters;
	
	//her laver vi vores temperature målinger med 100ms delay
	while(1) {
		int returnCode = hih8120_wakeup();
		if(returnCode!= HIH8120_OK && returnCode != HIH8120_TWI_BUSY) {
			printf("Temperature wakeup error: %d\n", returnCode);
		}
		
		vTaskDelay(100);
		returnCode = hih8120_measure();
		if (returnCode != HIH8120_OK && returnCode != HIH8120_TWI_BUSY) {
			printf("Temperature measure error: %d\n", returnCode);

		}
		vTaskDelay(5);
		

		//semaphore:
		xSemaphoreTake(semaphore, portMAX_DELAY);
		
		terrariumdata.humidity =hih8120_getHumidity();
		terrariumdata.temperature = hih8120_getTemperature_x10();
		printf("Fugtighed: %d%% Temperatur: %dC°\n", terrariumdata.humidity, terrariumdata.temperature);
		xSemaphoreGive(semaphore);

	}

	vTaskDelete(NULL);
}


float messureTemp()
{
	int returnCode = hih8120_wakeup();
	if(returnCode!= HIH8120_OK && returnCode != HIH8120_TWI_BUSY) {
		printf("Temperature wakeup error: %d\n", returnCode);
	}
	
	vTaskDelay(100);
	returnCode = hih8120_measure();
	if (returnCode != HIH8120_OK && returnCode != HIH8120_TWI_BUSY) {
		printf("Temperature measure error: %d\n", returnCode);

	}
	vTaskDelay(5);

	//semaphore:
	//xSemaphoreTake(semaphore, portMAX_DELAY);
	
	float temperature = hih8120_getTemperature();
	printf("Fugtighed: %d%% Temperatur: %dC°\n",temperature);
	return 	temperature;
}