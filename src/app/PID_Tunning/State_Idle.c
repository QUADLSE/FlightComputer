/*
 * Config.c
 *
 *  Created on: Mar 3, 2012
 *      Author: Alan
 */

#include "base.h"

#include "qGPIO.h"
#include "ESC.h"
#include "qFSM.h"
#include "qLeds.h"

/* ================================ */
/* Prototypes	 					*/
/* ================================ */

void Idle_Task(void * pvParameters);
void Idle_onEntry(void * pvParameters);
void Idle_onExit(void * pvParameters);

/* ================================ */
/* Private globals 					*/
/* ================================ */
static xTaskHandle hnd;

void Idle_onEntry(void * p){
	xTaskCreate(Idle_Task, ( signed char * ) "IDLE", 200, ( void * ) NULL, 1, &hnd );
}

void Idle_onExit(void * p){
	vTaskDelete(hnd);
}

void Idle_Task(void * pvParameters){
	int i;

	for (i=1;i<=4;i++)
	{
		ESC_SetChannel(i);
		ESC_SetSpeed(i,0);
	}

	for (;;){
		qLedsFlash(2,50);
		vTaskDelay(500/portTICK_RATE_MS);
	}
}

