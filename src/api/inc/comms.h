/*
 * comms.h
 *
 *  Created on: Jan 13, 2012
 *      Author: Alan
 */

#ifndef COMMS_H_
#define COMMS_H_

#ifndef MY_ADDRESS
	#error "A device address must be specified!"
#endif

#include <stdint.h>
#include "base.h"
#include "../API_Config.h"

//===========================================================
// Defines
//===========================================================
#define COMMS_HEADER 0xEA

//===========================================================
// Types
//===========================================================
typedef enum {
	MSG_TYPE_SYSTEM=0,
	MSG_TYPE_CONTROL,
	MSG_TYPE_DEBUG,
	MSG_TYPE_TELEMETRY
} DataType_t;


typedef struct{
	uint8_t 		SourceAddress;
	uint8_t 		DestAddress;
	uint8_t 		TimeStamp;
	DataType_t		Type;
	uint8_t			Length;
	uint8_t  *		Payload;
	uint8_t			Checksum;
}Msg_t;


typedef enum {
	MSG_STATE_HEADER,
	MSG_STATE_SOURCE,
	MSG_STATE_DEST,
	MSG_STATE_TIME,
	MSG_STATE_TYPE,
	MSG_STATE_LENGTH,
	MSG_STATE_PAYLOAD,
	MSG_STATE_CHECKSUM,
} Msg_Parser_State_t;

//===========================================================
// Prototypes
//===========================================================
uint32_t _qComms_getCurrentTimeStamp();
void _qComms_CreateMsg (uint8_t dest, DataType_t type, size_t size, uint8_t * payload, Msg_t * m);
ret_t qComms_SendMsg(uint8_t dest, DataType_t type, size_t size, uint8_t * payload);
ret_t qComms_ParseByte(Msg_t * buffer, uint8_t b);
#endif /* COMMS_H_ */
