/*
 * IMU.h
 *
 *  Created on: 07/02/2012
 *      Author: Eze
 */

#ifndef qIMU_H_
#define qIMU_H_

#include "base.h"

enum qIMU_enumSendDataType
{
	BINARY,
	CHARACTER,
};
typedef enum qIMU_enumSendDataType qIMU_eSendDataType;

enum qIMU_enumSensorDataType
{
	RAW,
	STANDARD,
	PROCESSED,
};
typedef enum qIMU_enumSensorDataType qIMU_eSensorDataType;

enum qIMU_enumBehavior
{
	POLL,
	CONTINUOS,
};
typedef enum qIMU_enumBehavior qIMU_eBehavior;

// TODO
//struct qIMU_typeData
//{
//};

void qIMU_Config (qIMU_eSendDataType sendDataType, qIMU_eSensorDataType sensorDataType, qIMU_eBehavior behavior);

ret_t qIMU_Init ();

ret_t qIMU_DeInit ();

void qIMU_Read ();

#endif /* IMU_H_ */
