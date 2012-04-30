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

	uint8_t * data;

	for (;;){
		xQueueReceive(ControlQueue,&data,portMAX_DELAY);
		switch (data[0]){
			case 'Q':
			case 'q':
				if (Speed<1000){
					ConsolePuts("Motor+\n",BLUE);
					Speed+=10;
				}
				break;

			case 'A':
			case 'a':
				if (Speed>10){
					ConsolePuts("Motor-\n",BLUE);
					Speed-=10;
				}
				break;
			default:
				break;
		}

		for (i=1;i<=4;i++)
		{
			ESC_SetChannel(i);
			ESC_SetSpeed(i,Speed);
		}

	}
}

