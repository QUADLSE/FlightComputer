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

void Manual_Task(void * pvParameters);
void Manual_onEntry(void * pvParameters);
void Manual_onExit(void * pvParameters);

/* ================================ */
/* Public globals 					*/
/* ================================ */
State_t State_Manual = {STATE_MANUAL,Manual_onEntry,Manual_onExit};

/* ================================ */
/* Private globals 					*/
/* ================================ */
static xTaskHandle hnd;

void Manual_onEntry(void * p){
	xTaskCreate(Manual_Task, ( signed char * ) "MANUAL", 500, ( void * ) NULL, 1, &hnd );
}

void Manual_onExit(void * p){
	vTaskDelete(hnd);
}

void Manual_Task(void * pvParameters){
	int i;
	for (;;){
		vTaskDelay(500/portTICK_RATE_MS);
	}
}

