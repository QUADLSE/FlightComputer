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
#include "DebugConsole.h"

/* ================================ */
/* Prototypes	 					*/
/* ================================ */
void Config_Task(void * pvParameters);
void Config_onEntry(void * pvParameters);
void Config_onExit(void * pvParameters);

/* ================================ */
/* Public globals 					*/
/* ================================ */
State_t State_Init = {STATE_INIT,Config_onEntry,Config_onExit};

/* ================================ */
/* Private globals 					*/
/* ================================ */
static xTaskHandle hnd;

void Config_onEntry(void * p){
	xTaskCreate(Config_Task, ( signed char * ) "SYSTEM", 500, ( void * ) NULL, 1, &hnd );
}

void Config_onExit(void * p){
	vTaskDelete(hnd);
}

void Config_Task(void * pvParameters){

	extern State_t State_Idle;

	/* -------------------------------------- */
	/*	Leds Init							  */
	/* -------------------------------------- */
	qLedsInit();
	qLedsFlash(3,100);


	/* -------------------------------------- */
	/*	Comms Init							  */
	/* -------------------------------------- */

	if (qUART_Init(UART_GROUND,57600,8,QUART_PARITY_NONE,8)==RET_ERROR){
		while(1);
	}
	//qUART_Register_RBR_Callback(UART_GROUND, UART_Rx_Handler);

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
	ConsolePuts("QUADLSE V1.0 Initialized...\r\n",GREEN);
	qLedsAnimation(2);

	/* Terminate and go to Idle */
	ChangeState(&State_Idle);

}

