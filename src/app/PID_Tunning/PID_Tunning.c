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
#include "ESC.h"
#include "qIMU.h"

#if 0
typedef enum{
	STATE_CONFIG,
	STATE_IDLE,
	STATE_RUNNING,
	STATE_ERROR
} system_states_t;

system_states_t state=STATE_CONFIG;
#endif

void sys(void *);
void configSystem(void *);
void IMUTest(void * pvParameters);

void App_UARTRxHandler (uint8_t * buff, size_t sz);
uint8_t sendBlocked = TRUE;

qIMU_tDataTest IMUData;

void AppMain(void) {

	xTaskCreate(configSystem, ( signed char * ) "CONFIG", 1000, ( void * ) NULL, 1, NULL );
	vTaskStartScheduler();

	for(;;);
}


void configSystem(void * pvParameters){

	int i;

	/* -------------------------------------- */
	/*	GPIO Init							  */
	/* -------------------------------------- */
	qGPIO_Init(0,qGPIO_OUTPUT);
	qGPIO_Init(1,qGPIO_OUTPUT);
	qGPIO_Init(2,qGPIO_OUTPUT);
	qGPIO_Init(3,qGPIO_OUTPUT);

	/* -------------------------------------- */
	/*	ESC Init							  */
	/* -------------------------------------- */
	ESC_Init(1,50,1000,2000);

	for (i=1;i<=4;i++)
	{
		ESC_SetChannel(i);
		//ESC_SetSpeed(i,100);
		ESC_SetSpeed(i,0);
	}

	/* -------------------------------------- */
	/*	IMU Init							  */
	/* -------------------------------------- */
	//qIMU_Config (BINARY, PROCESSED, POLL, 2, 57600, 8, QUART_PARITY_NONE, 1);
	qIMU_Init (BINARY, PROCESSED, POLL, 2, 57600, 8, QUART_PARITY_NONE, 1);
	qIMU_Reset();

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

	//xTaskCreate(IMUTest, ( signed char * ) "CONFIG", 300, ( void * ) NULL, 1, NULL );

	xTaskCreate(Communications, ( signed char * ) "COMMS", 1000, ( void * ) NULL, 1, NULL );
	xTaskCreate(PID_Task, ( signed char * ) "CONFIG", 1000, ( void * ) NULL, 2, NULL );

	/* Auto delete */
	vTaskDelete(NULL);
}

#if 0

void IMUTest(void * pvParameters){

	while (1)
	{
		while (sendBlocked == TRUE);
		qIMU_ReadTest (&IMUData);
		qUART_SendByte(0, qIMU_HEADER);
		qUART_SendByte(0, IMUData.yawH);
		qUART_SendByte(0, IMUData.yawL);
		qUART_SendByte(0, IMUData.pitchH);
		qUART_SendByte(0, IMUData.pitchL);
		qUART_SendByte(0, IMUData.rollH);
		qUART_SendByte(0, IMUData.rollL);
		qUART_SendByte(0, IMUData.gyroYawH);
		qUART_SendByte(0, IMUData.gyroYawL);
		qUART_SendByte(0, IMUData.gyroPitchH);
		qUART_SendByte(0, IMUData.gyroPitchL);
		qUART_SendByte(0, IMUData.gyroRollH);
		qUART_SendByte(0, IMUData.gyroRollH);
		qUART_SendByte(0, qIMU_FOOTER);
		sendBlocked = TRUE;
	}
}

void App_UARTRxHandler (uint8_t * buff, size_t sz)
{
	sendBlocked = FALSE;
}
#endif


