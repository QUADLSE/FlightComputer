/*
 * main.c
 *
 *  Created on: Feb 8, 2012
 *      Author: Eze
 */

#include <stdint.h>

#include "qIMU.h"
#include "qUART.h"

void App_UARTRxHandler (uint8_t * buff, size_t sz);
uint8_t sendBlocked = TRUE;

int AppMain(void)
{
	qIMU_tDataTest IMUData;

	qIMU_Config (BINARY, TEST, POLL, 1, 57600, 8, QUART_PARITY_NONE, 1);
	qIMU_Init ();

	if (qUART_Init(2, 57600, 8, QUART_PARITY_NONE, 1) == RET_ERROR)
	{
			while(1);
	}
	qUART_Register_RBR_Callback(2, App_UARTRxHandler);
	qUART_SendByte(2, qIMU_HEADER);

	while (1)
	{
		while (sendBlocked == TRUE);
		qIMU_ReadTest (&IMUData);
		qUART_SendByte(2, '\r');
		qUART_SendByte(2, '\n');
		qUART_SendByte(2, IMUData.yawH);
		qUART_SendByte(2, IMUData.yawL);
		qUART_SendByte(2, IMUData.pitchH);
		qUART_SendByte(2, IMUData.pitchL);
		qUART_SendByte(2, IMUData.rollH);
		qUART_SendByte(2, IMUData.rollL);
		qUART_SendByte(2, IMUData.gyroYawH);
		qUART_SendByte(2, IMUData.gyroYawL);
		qUART_SendByte(2, IMUData.gyroPitchH);
		qUART_SendByte(2, IMUData.gyroPitchL);
		qUART_SendByte(2, IMUData.gyroRollH);
		qUART_SendByte(2, IMUData.gyroRollH);
		qUART_SendByte(2, '\r');
		qUART_SendByte(2, '\n');
		sendBlocked = TRUE;
	}

	return 0;
}

void App_UARTRxHandler (uint8_t * buff, size_t sz)
{
	sendBlocked = FALSE;
}
