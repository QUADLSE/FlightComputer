/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : Quadrotor On board computer
===============================================================================
*/

#include "base.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "tasks/tasklist.h"

#include "qGPIO.h"
#include "qCOMMS.h"
#include "qUART.h"
#include "ESC.h"//DANI
#include "qIMU.h"

typedef enum{
	STATE_CONFIG,
	STATE_IDLE,
	STATE_RUNNING,
	STATE_ERROR
} system_states_t;

system_states_t state=STATE_CONFIG;

void sys(void *);
void configSystem(void *);

void AppMain(void) {

	/*xTaskCreate(Communications, ( signed char * ) "COMMS", configMINIMAL_STACK_SIZE, ( void * ) NULL, 1, NULL );*/
	/*xTaskCreate(Telemetry, ( signed char * ) "TELEMETRY", 300, ( void * ) NULL, 1, NULL );*/
	/*xTaskCreate(sys, ( signed char * ) "SYSTEM", 300, ( void * ) NULL, 1, NULL );*/

	xTaskCreate(configSystem, ( signed char * ) "CONFIG", 300, ( void * ) NULL, 1, NULL );

	vTaskStartScheduler();

	for(;;);
}

/*
void sys(void * pvParameters){
	switch (state){
		case STATE_CONFIG:
			configSystem();
			break;
		case STATE_IDLE:
			break;
		case STATE_RUNNING:
			break;
		case STATE_ERROR:
			break;
	}
}

*/
void configSystem(void * pvParameters){

	char HelloMsg[]={"QUADLSE v1.0 Initialized.\r\n"};
	uint8_t i;

	qGPIO_Init(0,qGPIO_OUTPUT);
	qGPIO_Init(1,qGPIO_OUTPUT);
	qGPIO_Init(2,qGPIO_OUTPUT);
	qGPIO_Init(3,qGPIO_OUTPUT);

	qUART_Init(0,115200,8,QUART_PARITY_NONE,1);


	ESC_Init(1,50,5000,6000);

	for (i=1;i<=4;i++)
	{
		ESC_SetChannel(i);
		ESC_SetSpeed(i,0);
	}

	//ESC_SetSpeed(0,speed);

	qComms_SendMsg(0,0xAA,MSG_TYPE_DEBUG,strlen(HelloMsg),HelloMsg);

	/*----------------------------------------------*/
	/* Led show! yuhu!*/
	/*----------------------------------------------*/
	for (i=0;i<3;i++){
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

	/* Auto delete */
	vTaskDelete(NULL);
}

