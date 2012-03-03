/*
 * Config.c
 *
 *  Created on: Mar 3, 2012
 *      Author: Alan
 */

#include "base.h"

#include "qGPIO.h"
#include "qCOMMS.h"
#include "ESC.h"
#include "qIMU.h"
#include "qFSM.h"
#include "qLeds.h"

void Config_Task(void * pvParameters);
void Config_onEntry(void * pvParameters);
void Config_onExit(void * pvParameters);

State_t State_Init = {STATE_INIT,Config_onEntry,Config_onExit};

void Config_onEntry(void * p){
	xTaskCreate(Config_Task, ( signed char * ) "SYSTEM", 500, ( void * ) NULL, 1, NULL );
}

void Config_onExit(void * p){

}
void Config_Task(void * pvParameters){

	qLedsInit();
	qLedsFlash(3,100);

	/* -------------------------------------- */
	/*	ESC Init							  */
	/* -------------------------------------- */
	ESC_Init(1,50,1000,2000);

	int i;
	for (i=1;i<=4;i++)
	{
		ESC_SetChannel(i);
		//ESC_SetSpeed(i,100);
		ESC_SetSpeed(i,0);
	}

	/* -------------------------------------- */
	/*	IMU Init							  */
	/* -------------------------------------- */
	//qIMU_Init (BINARY, PROCESSED, POLL, 2, 57600, 8, QUART_PARITY_NONE, 1);
	//qIMU_Reset();

	/*----------------------------------------------*/
	/* Everything OK! Led show! yuhu!*/
	/*----------------------------------------------*/
	qLedsAnimation(2);

	//xTaskCreate(IMUTest, ( signed char * ) "CONFIG", 300, ( void * ) NULL, 1, NULL );
	//xTaskCreate(Communications, ( signed char * ) "COMMS", 1000, ( void * ) NULL, 1, NULL );
	//xTaskCreate(PID_Task, ( signed char * ) "CONFIG", 1000, ( void * ) NULL, 2, NULL );

	/* Auto delete */
	vTaskDelete(NULL);
}

