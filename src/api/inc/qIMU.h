/*
 * IMU.h
 *
 *  Created on: 07/02/2012
 *      Author: Eze
 */

#ifndef qIMU_H_
#define qIMU_H_

#include <stdint.h>

#include "base.h"
#include "qUART.h"

#define qIMU_HEADER 			0xFF
#define qIMU_FOOTER				0xF1
#define qIMU_ACK				0xAA
#define qIMU_READ				0xBB

#ifndef TRUE
#define TRUE 					1
#endif

#ifndef FALSE
#define FALSE					0
#endif

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
	TEST,
};
typedef enum qIMU_enumSensorDataType qIMU_eSensorDataType;

enum qIMU_enumBehavior
{
	POLL,
	CONTINUOS,
};
typedef enum qIMU_enumBehavior qIMU_eBehavior;

enum qIMU_enumState
{
	INITIALIZING,
	DEINITIALIZING,
	READING,
	IDLE,
};
typedef enum qIMU_enumState qIMU_eState;

enum qIMU_enumState_Init
{
	SENDING_INIT_HEADER,
	SENDING_DATATYEPE,
	SENDING_SENSORDATATYPE,
	SENDING_BEHAVIOR,
	SENDING_INIT_FOOTER,
	RECEIVING_ACK,
};
typedef enum qIMU_enumState_Init qIMU_eState_Init;

enum qIMU_enumState_DeInit
{
	SENDING_DEINIT_HEADER,
};
typedef enum qIMU_enumState_DeInit qIMU_eState_DeInit;

enum qIMU_enumState_Read
{
	SENDING_READ_HEADER,
	RECEIVING_READ_HEADER,
	RECEIVING_DATA,
	RECEIVING_READ_FOOTER,
};
typedef enum qIMU_enumState_Read qIMU_eState_Read;

struct qIMU_typeDataRaw
{
	uint16_t accX;
	uint16_t accY;
	uint16_t accZ;
	uint16_t gyroPitch;
	uint16_t gyroRoll;
	uint16_t gyroYaw;
	uint16_t magX;
	uint16_t magY;
	uint16_t magZ;
};
typedef struct qIMU_typeDataRaw qIMU_tDataRaw;

struct qIMU_typeDataStandard
{
	float accX;
	float accY;
	float accZ;
	float gyroPitch;
	float gyroRoll;
	float giroYaw;
	float magX;
	float magY;
	float magZ;
};
typedef struct qIMU_typeDataStandard qIMU_tDataStandard;

struct qIMU_typeDataProcessed
{
	float pitch;
	float roll;
	float yaw;
	float gyroPitch;
	float gyroRoll;
	float gyroYaw;
};
typedef struct qIMU_typeDataProcessed qIMU_tDataProcessed;

struct qIMU_typeDataTest
{
	uint8_t pitchH;
	uint8_t pitchL;
	uint8_t rollH;
	uint8_t rollL;
	uint8_t yawH;
	uint8_t yawL;
	uint8_t gyroPitchH;
	uint8_t gyroPitchL;
	uint8_t gyroRollH;
	uint8_t gyroRollL;
	uint8_t gyroYawH;
	uint8_t gyroYawL;
};
typedef struct qIMU_typeDataTest qIMU_tDataTest;

extern qIMU_eSendDataType qIMU_sendDataType;
extern qIMU_eSensorDataType qIMU_sensorDaraType;
extern qIMU_eBehavior qIMU_behavior;

extern uint8_t qIMU_UARTid;

extern qIMU_eState qIMU_state;
extern qIMU_eState_Init qIMU_state_init;
extern qIMU_eState_DeInit qIMU_state_deInit;
extern qIMU_eState_Read qIMU_state_read;

extern uint8_t qIMU_init_blocked;
extern uint8_t qIMU_read_blocked;

extern qIMU_tDataRaw qIMU_DataRaw;
extern qIMU_tDataStandard qIMU_DataStandard;
extern qIMU_tDataProcessed qIMU_DataProcessed;
extern qIMU_tDataTest qIMU_DataTest;

void qIMU_Config (qIMU_eSendDataType sendDataType, qIMU_eSensorDataType sensorDataType, qIMU_eBehavior behavior,
				  uint8_t id, uint32_t BaudRate, uint8_t DataBits, qUART_Parity_t Parity, uint8_t StopBits);

ret_t qIMU_Init ();

ret_t qIMU_DeInit ();

void qIMU_ReadRaw (qIMU_tDataRaw* pData);

void qIMU_ReadStandard (qIMU_tDataStandard* pData);

void qIMU_ReadProcessed (qIMU_tDataProcessed* pData);

void qIMU_ReadTest (qIMU_tDataTest* pData);

void qIMU_UARTRxHandler(uint8_t * buff, size_t sz);

// ********************************************************************************************************
// ******************************************* Private Methods ********************************************
// ********************************************************************************************************
void qIMU_Initializing_VM (uint8_t * buff, size_t sz);
void qIMU_DeInitializing_VM (uint8_t * buff, size_t sz);
void qIMU_Reading_VM (uint8_t * buff, size_t sz);
// ********************************************************************************************************
// ********************************************************************************************************
// ********************************************************************************************************

#endif /* IMU_H_ */
