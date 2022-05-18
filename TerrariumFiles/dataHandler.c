/*
 * dataHandler.c
 *
 * Created: 16-05-2022 10:55:45
 *  Author: Solaiman
 */ 

#include "dataHandler.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct Terrariumdata {
	float temperature;
	int16_t messurementCount;
} Terrariumdata;


Terrariumdata_p createTerrarium(){
	Terrariumdata_p newTerrarium = (Terrariumdata_p)calloc(sizeof (Terrariumdata),1);
	if(newTerrarium == NULL)
	{
		printf("could not allocate memory");
		return NULL;
	}
	return newTerrarium;
}

void messure(Terrariumdata_p terrariumdata)
{
	terrariumdata->temperature += getTemperature();
	terrariumdata->messurementCount += 1 ;
}

void prepareData(Terrariumdata_p terrariumdata)
{
	int16_t messurementCount = terrariumdata->messurementCount;
	float temperature = terrariumdata->temperature;
	 
	terrariumdata->temperature =  temperature/messurementCount;
}

void wipeData(Terrariumdata_p terrariumdata)
{
    terrariumdata->messurementCount = 0;
	terrariumdata->temperature = 0;
}




