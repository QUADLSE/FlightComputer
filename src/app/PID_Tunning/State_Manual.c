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

#include "string.h"
#include "DebugConsole.h"

extern xQueueHandle ControlQueue;


/* ================================ */
/* Prototypes	 					*/
/* ================================ */

void Fligth_Manual_Task(void * pvParameters);
void Fligth_Manual_onEntry(void * pvParameters);
void Fligth_Manual_onExit(void * pvParameters);

/* ================================ */
/* Private globals 					*/
/* ================================ */
static xTaskHandle hnd;

void Fligth_Manual_onEntry(void * p){

	xTaskCreate(Fligth_Manual_Task, ( signed char * ) "MANUAL", 500, ( void * ) NULL, 1, &hnd );

}

void Fligth_Manual_onExit(void * p){
	vTaskDelete(hnd);
}

uint32_t Speed = 0;

void Fligth_Manual_Task(void * pvParameters){
	int i;

	uint32_t * datax;
	uint32_t * datay;
	uint32_t * dataz;
	uint32_t * datar;

	for (;;)
	{
		xQueueReceive(ControlQueue,&datax,portMAX_DELAY);
		ESC_SetChannel(1);
		ESC_SetSpeed(1,datax);
		ConsolePuts("Motor1:",BLUE);
		ConsolePuts(itoa(datax),GREEN);

		xQueueReceive(ControlQueue,&datay,portMAX_DELAY);
		ESC_SetChannel(2);
		ESC_SetSpeed(2,datay);
		ConsolePuts("Motor2:",BLUE);
		ConsolePuts(itoa(datay),GREEN);

		xQueueReceive(ControlQueue,&dataz,portMAX_DELAY);
		ESC_SetChannel(3);
		ESC_SetSpeed(3,dataz);
		ConsolePuts("Motor3:",BLUE);
		ConsolePuts(itoa(dataz),GREEN);

		xQueueReceive(ControlQueue,&datar,portMAX_DELAY);
		ESC_SetChannel(4);
		ESC_SetSpeed(4,datar);
		ConsolePuts("Motor4:",BLUE);
		ConsolePuts(itoa(datar),GREEN);

	}
}

