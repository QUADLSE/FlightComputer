/*
 * IMU.c
 *
 *  Created on: 07/02/2012
 *      Author: Eze
 */

#include <stdint.h>

#include "base.h"
#include "qIMU.h"
#include "qUART.h"

qIMU_eSendDataType qIMU_sendDataType = BINARY;
qIMU_eSensorDataType qIMU_sensorDataType = PROCESSED;
qIMU_eBehavior qIMU_behavior = POLL;

uint8_t qIMU_UARTid;

qIMU_eState qIMU_state;
qIMU_eState_Init qIMU_state_init;
qIMU_eState_DeInit qIMU_state_deInit;
qIMU_eState_Read qIMU_state_read;

uint8_t qIMU_init_blocked;
uint8_t qIMU_read_blocked;

qIMU_tDataRaw qIMU_DataRaw;
qIMU_tDataStandard qIMU_DataStandard;
qIMU_tDataProcessed qIMU_DataProcessed;
qIMU_tDataTest qIMU_DataTest;

void qIMU_Config (qIMU_eSendDataType sendDataType, qIMU_eSensorDataType sensorDataType, qIMU_eBehavior behavior,
				  uint8_t id, uint32_t BaudRate, uint8_t DataBits, qUART_Parity_t Parity, uint8_t StopBits)
{
	qIMU_sendDataType = sendDataType;
	qIMU_sensorDataType = sensorDataType;
	qIMU_behavior = behavior;
	if (qUART_Init(id, BaudRate, DataBits, Parity, StopBits) == RET_ERROR)
	{
		while(1);
	}
	qIMU_UARTid = id;
	qUART_Register_RBR_Callback(id, qIMU_UARTRxHandler);
}

ret_t qIMU_Init ()
{
	qIMU_state = INITIALIZING;
	qIMU_state_init = SENDING_INIT_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_HEADER);

	qIMU_state_init = SENDING_BEHAVIOR;
	switch (qIMU_behavior)
	{
		case POLL:
			qUART_SendByte(qIMU_UARTid, 0x00); //FIXME: Hardcoded
		break;
		case CONTINUOS:
			qUART_SendByte(qIMU_UARTid, 0x01); //FIXME: Hardcoded
		break;
	}

	qIMU_state_init = SENDING_SENSORDATATYPE;
	switch (qIMU_sensorDataType)
	{
		case RAW:
			qUART_SendByte(qIMU_UARTid, 0x02); //FIXME: Hardcoded
		break;
		case STANDARD:
			qUART_SendByte(qIMU_UARTid, 0x01); //FIXME: Hardcoded
		break;
		case PROCESSED:
			qUART_SendByte(qIMU_UARTid, 0x00); //FIXME: Hardcoded
		break;
		case TEST:
			qUART_SendByte(qIMU_UARTid, 0x00); //FIXME: Hardcoded
		break;
	}

	qIMU_state_init = SENDING_DATATYEPE;
	switch (qIMU_sendDataType)
	{
		case BINARY:
			qUART_SendByte(qIMU_UARTid, 0x01); //FIXME: Hardcoded
		break;
		case CHARACTER:
			qUART_SendByte(qIMU_UARTid, 0x00); //FIXME: Hardcoded
		break;
	}

	qIMU_state_init = SENDING_INIT_FOOTER;
	qUART_SendByte(qIMU_UARTid, qIMU_FOOTER); //FIXME: Hardcoded

	qIMU_state_init = RECEIVING_ACK;

	qIMU_init_blocked = TRUE;
	while (qIMU_init_blocked == TRUE);
}


ret_t qIMU_DeInit ()
{

}

void qIMU_ReadTest (qIMU_tDataTest* pData)
{
	qIMU_state = READING;
	qIMU_state_read = SENDING_READ_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_READ);

	qIMU_state_read = RECEIVING_READ_HEADER;
	qIMU_read_blocked = TRUE;
	while (qIMU_read_blocked == TRUE);

	pData->yawH = qIMU_DataTest.yawH;
	pData->yawL = qIMU_DataTest.yawL;
	pData->pitchH = qIMU_DataTest.pitchH;
	pData->pitchL = qIMU_DataTest.pitchL;
	pData->rollH = qIMU_DataTest.rollH;
	pData->rollL = qIMU_DataTest.rollL;
	pData->gyroYawH = qIMU_DataTest.gyroYawH;
	pData->gyroYawL = qIMU_DataTest.gyroYawL;
	pData->gyroPitchH = qIMU_DataTest.gyroPitchH;
	pData->gyroPitchL = qIMU_DataTest.gyroPitchL;
	pData->gyroRollH = qIMU_DataTest.gyroRollH;
	pData->gyroPitchL = qIMU_DataTest.gyroRollL;
}


// TODO: ReadRaw () - ReadStandard () - ReadProcessed

void qIMU_UARTRxHandler(uint8_t * buff, size_t sz)
{
	uint8_t i;

	switch (qIMU_state)
	{
		case INITIALIZING:
			qIMU_Initializing_VM (buff, sz);
		break;

		case DEINITIALIZING:
			qIMU_DeInitializing_VM (buff, sz);
		break;

		case READING:
			qIMU_Reading_VM (buff, sz);
		break;

		case IDLE:
		break;
	}

}

void qIMU_Initializing_VM (uint8_t * buff, size_t sz)
{
	switch (qIMU_state_init)
	{
		case RECEIVING_ACK:
			if (*buff == qIMU_ACK)
			{
				qIMU_init_blocked = FALSE;
				qIMU_state = IDLE;
			}
			else
			{
				// FIXME: Ver que hacer si el dato es falso
			}
		break;
	}
}

void qIMU_DeInitializing_VM (uint8_t * buff, size_t sz)
{
	switch (qIMU_state_deInit)
	{

	}
}


void qIMU_Reading_VM (uint8_t * buff, size_t sz)
{
	int i;

	if (qIMU_state_read == RECEIVING_READ_HEADER)
	{
		if (*buff == qIMU_HEADER)
		{
			qIMU_state_read = RECEIVING_DATA;
			switch (qIMU_sensorDataType)
			{
				case PROCESSED:
					qIMU_DataProcessed.yaw = ((*(buff+1))<<8) + (*(buff+2));
					qIMU_DataProcessed.pitch = ((*(buff+3))<<8) + (*(buff+4));
					qIMU_DataProcessed.roll = ((*(buff+5))<<8) + (*(buff+6));
					qIMU_DataProcessed.gyroYaw = ((*(buff+7))<<8) + (*(buff+8));
					qIMU_DataProcessed.gyroPitch = ((*(buff+9))<<8) + (*(buff+10));
					qIMU_DataProcessed.gyroRoll = ((*(buff+11))<<8) + (*(buff+12));
				break;

				case TEST:
				{
					qIMU_DataTest.yawH = *(buff + 1);
					qIMU_DataTest.yawL = *(buff + 2);
					qIMU_DataTest.pitchH = *(buff + 3);
					qIMU_DataTest.pitchL = *(buff + 4);
					qIMU_DataTest.rollH = *(buff + 5);
					qIMU_DataTest.rollL = *(buff + 6);
					qIMU_DataTest.gyroYawH = *(buff + 7);
					qIMU_DataTest.gyroYawL = *(buff + 8);
					qIMU_DataTest.gyroPitchH = *(buff + 9);
					qIMU_DataTest.gyroPitchL = *(buff + 10);
					qIMU_DataTest.gyroRollH = *(buff + 11);
					qIMU_DataTest.gyroRollL = *(buff + 12);
				}
			}

			qIMU_state_read = RECEIVING_READ_FOOTER;
			if (*(buff+13) == qIMU_FOOTER)
			{
				qIMU_read_blocked = FALSE;
			}
			else
			{
				// FIXME: Ver que hacer en caso de error
			}
		}
		else
		{
			// FIXME: Ver que hacer en caso de error
		}
	}
	else
	{
		// FIXME: Ver que hacer en caso de error
	}
}
