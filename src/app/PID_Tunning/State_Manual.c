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

void Fligth_Manual_Task(void * pvParameters)
{
	int i;

	int32_t * data[6];

	for (;;)
	{
		if(xQueueReceive(ControlQueue,&data,portMAX_DELAY))
		{


		ESC_SetChannel(1);
		ESC_SetSpeed(1,(int32_t)data[2]);
		ESC_SetChannel(2);
		ESC_SetSpeed(2,(int32_t)data[3]);
		ESC_SetChannel(3);
		ESC_SetSpeed(3,(int32_t)data[4]);
		ESC_SetChannel(4);
		ESC_SetSpeed(4,(int32_t)data[5]);


#if CONSOLE_DEBUG_RECEIVER
		char msg[4];
		ConsolePuts("Recibi dato.\n",BLUE);

		itoa(data[2], msg, 10);
		ConsolePuts("Motor1:",BLUE);
		ConsolePuts(msg,GREEN);
		ConsolePuts("; ",BLUE);

		itoa(data[3], msg, 10);
		ConsolePuts("Motor2:",BLUE);
		ConsolePuts(msg,GREEN);
		ConsolePuts("; ",BLUE);

		itoa(data[4], msg, 10);
		ConsolePuts("Motor3:",BLUE);
		ConsolePuts(msg,GREEN);
		ConsolePuts("; ",BLUE);

		itoa(data[5], msg, 10);
		ConsolePuts("Motor4:",BLUE);
		ConsolePuts(msg,GREEN);
		ConsolePuts("\n",BLUE);
#endif

		}
	}

#if 0
		//ESC_SetChannel(2);
	//	ESC_SetSpeed(2,data[1]);
		ConsolePuts("Motor2:",BLUE);
	//	ConsolePuts(itoa(data[1]),GREEN);

		//ESC_SetChannel(3);
		//ESC_SetSpeed(3,data[2]);
		ConsolePuts("Motor3:",BLUE);
//		ConsolePuts(itoa(data[2]),GREEN);

		//ESC_SetChannel(4);
		//ESC_SetSpeed(4,data[3]);
		ConsolePuts("Motor4:",BLUE);
	//	ConsolePuts(itoa(data[3]),GREEN);

	}
#endif
}

