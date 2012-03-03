/*
 * Leds.c
 *
 *  Created on: Mar 3, 2012
 *      Author: Alan
 */

#include "qLeds.h"
#include "qGPIO.h"

void qLedsInit(){
	qGPIO_Init(0,qGPIO_OUTPUT);
	qGPIO_Init(1,qGPIO_OUTPUT);
	qGPIO_Init(2,qGPIO_OUTPUT);
	qGPIO_Init(3,qGPIO_OUTPUT);
}

void qLedsFlash(int times, int period){
	while ((times--)>0){
		qGPIO_Set(0,qGPIO_HIGH);
		qGPIO_Set(1,qGPIO_HIGH);
		qGPIO_Set(2,qGPIO_HIGH);
		qGPIO_Set(3,qGPIO_HIGH);
		vTaskDelay(period/portTICK_RATE_MS);
		qGPIO_Set(0,qGPIO_LOW);
		qGPIO_Set(1,qGPIO_LOW);
		qGPIO_Set(2,qGPIO_LOW);
		qGPIO_Set(3,qGPIO_LOW);
		vTaskDelay(period/portTICK_RATE_MS);
	}
}

void qLedsAnimation(int times){
	while ((times--)>0){
		qGPIO_Set(0,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(0,qGPIO_LOW);
		qGPIO_Set(1,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(1,qGPIO_LOW);
		qGPIO_Set(2,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(2,qGPIO_LOW);
		qGPIO_Set(3,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(3,qGPIO_LOW);

		qGPIO_Set(3,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(3,qGPIO_LOW);
		qGPIO_Set(2,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(2,qGPIO_LOW);
		qGPIO_Set(1,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(1,qGPIO_LOW);
		qGPIO_Set(0,qGPIO_HIGH);
		vTaskDelay(50/portTICK_RATE_MS);
		qGPIO_Set(0,qGPIO_LOW);
	}
}
