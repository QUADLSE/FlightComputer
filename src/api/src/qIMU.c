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
qIMU_eState_Reset qIMU_state_reset;
qIMU_eState_Read qIMU_state_read;

uint8_t qIMU_init_blocked;
uint8_t qIMU_reset_blocked;
uint8_t qIMU_read_blocked;

qIMU_tDataRaw qIMU_DataRaw;
qIMU_tDataStandard qIMU_DataStandard;
qIMU_tDataProcessed qIMU_DataProcessed;
qIMU_tDataTest qIMU_DataTest;

ret_t qIMU_Init (qIMU_eSendDataType sendDataType, qIMU_eSensorDataType sensorDataType, qIMU_eBehavior behavior,
		  	     uint8_t id, uint32_t BaudRate, uint8_t DataBits, qUART_Parity_t Parity, uint8_t StopBits)
{
	// Set IMU configuration in globals
	qIMU_sendDataType = sendDataType;
	qIMU_sensorDataType = sensorDataType;
	qIMU_behavior = behavior;
	// Init the UART port for communicate IMU with LPC
	if (qUART_Init(id, BaudRate, DataBits, Parity, StopBits) == RET_ERROR)
	{
		while(1);
	}
	qIMU_UARTid = id;
	qUART_Register_RBR_Callback(id, qIMU_UARTRxHandler);

	// Send qIMU_PARAM_CONFIG for telling the IMU to enter in the configuration mode
	qIMU_state = INITIALIZING;
	qIMU_state_init = SENDING_INIT_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_PARAM_CONFIG);
	qUART_SendByte(qIMU_UARTid, qIMU_HEADER);

	// Set behavior
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

	// Set data type
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

	// Set sensor data type
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

	// Send footer
	qIMU_state_init = SENDING_INIT_FOOTER;
	qUART_SendByte(qIMU_UARTid, qIMU_FOOTER); //FIXME: Hardcoded

	// Init state: blocked
	// waiting for ack
	qIMU_state_init = RECEIVING_ACK;
	qIMU_init_blocked = TRUE;
	while (qIMU_init_blocked == TRUE);
}

ret_t qIMU_Reset ()
{
	// Send qIMU_PARAM_RESET for telling the IMU to enter in the reseting mode
	qIMU_state = RESETING;
	qIMU_state_reset = qIMU_Reset_SENDING_RESET_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_PARAM_RESET);

	// Reset state: blocked
	// waiting for ack
	qIMU_state_reset = qIMU_Reset_RECEIVING_ACK;
	qIMU_reset_blocked = TRUE;
	while (qIMU_reset_blocked == TRUE);
}

void qIMU_ReadTest (qIMU_tDataTest* pData)
{
	// Send qIMU_PARAM_READ for telling the IMU to enter in the reading mode
	qIMU_state = READING;
	qIMU_state_read = SENDING_READ_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_PARAM_READ);

	// Read state: blocked
	// waiting for ack
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

void qIMU_ReadProcessed (qIMU_tDataProcessed* pData)
{
	// Send qIMU_PARAM_RESET for telling the IMU to enter in the reading mode
	qIMU_state = READING;
	qIMU_state_read = SENDING_READ_HEADER;
	qUART_SendByte(qIMU_UARTid, qIMU_PARAM_READ);

	qIMU_state_read = RECEIVING_READ_HEADER;
	qIMU_read_blocked = TRUE;
	while (qIMU_read_blocked == TRUE);

	pData->yaw = qIMU_DataProcessed.yaw;
	pData->pitch = qIMU_DataProcessed.pitch;
	pData->roll = qIMU_DataProcessed.roll;
	pData->gyroYaw = qIMU_DataProcessed.gyroYaw;
	pData->gyroPitch = qIMU_DataProcessed.gyroPitch;
	pData->gyroRoll = qIMU_DataProcessed.gyroRoll;
}

// TODO: ReadRaw () - ReadStandard ()

void qIMU_UARTRxHandler(uint8_t * buff, size_t sz)
{
	uint8_t i;

	switch (qIMU_state)
	{
		case INITIALIZING:
			qIMU_Initializing_SM (buff, sz);
		break;

		case RESETING:
			qIMU_Reseting_SM (buff, sz);
		break;

		case READING:
			qIMU_Reading_SM (buff, sz);
		break;

		case IDLE:
		break;
	}

}

void qIMU_Initializing_SM (uint8_t * buff, size_t sz)
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

void qIMU_Reseting_SM (uint8_t * buff, size_t sz)
{
	switch (qIMU_state_reset)
	{
		case qIMU_Reset_RECEIVING_ACK:
			qIMU_reset_blocked = FALSE;
			qIMU_state = IDLE;
		break;
	}
}

void qIMU_Reading_SM (uint8_t * buff, size_t sz)
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
					qIMU_DataProcessed.yaw = (float)(((*(buff+2))<<8) + (*(buff+1)) - 20000) / 100.0;
					qIMU_DataProcessed.pitch = -(float)(((*(buff+4))<<8) + (*(buff+3)) - 20000) / 100.0;
					qIMU_DataProcessed.roll = -(float)(((*(buff+6))<<8) + (*(buff+5)) - 20000) / 100.0;
					qIMU_DataProcessed.gyroRoll = (float)(((*(buff+8))<<8) + (*(buff+7)) - 20000) / 10.0;
					qIMU_DataProcessed.gyroPitch = (float)(((*(buff+10))<<8) + (*(buff+9)) - 20000) / 10.0;
					qIMU_DataProcessed.gyroYaw = (float)(((*(buff+12))<<8) + (*(buff+11)) - 20000) / 10.0;
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
				qIMU_state = IDLE;
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
