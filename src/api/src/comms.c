/*
 * comms.c
 *
 *  Created on: Jan 13, 2012
 *      Author: Alan
 */

#include <stdint.h>
#include "base.h"
#include "comms.h"
#include "qUART.h"


uint32_t _qComms_getCurrentTimeStamp(){
	return 0x55;
}

void _qComms_CreateMsg (uint8_t dest, DataType_t type, size_t size, uint8_t * payload, Msg_t * m){

	m->SourceAddress = MY_ADDRESS;
	m->DestAddress = dest;
	m->TimeStamp = _qComms_getCurrentTimeStamp();
	m->Type = type;
	m->Length = size;
	m->Payload = payload;
	m->Checksum = (uint8_t)	(m->SourceAddress +
					m->DestAddress +
					m->TimeStamp +
					m->Length);
}

ret_t qComms_SendMsg(uint8_t dest, DataType_t type, size_t size,  uint8_t * payload){
	Msg_t MsgBuffer;

	_qComms_CreateMsg(dest,type,size,payload,&MsgBuffer);

	qUART_SendByte(UART_GROUNDCOMM,COMMS_HEADER);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.SourceAddress);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.DestAddress);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.TimeStamp);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.Type);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.Length);
	qUART_Send(UART_GROUNDCOMM,(uint8_t *)MsgBuffer.Payload,MsgBuffer.Length);
	qUART_SendByte(UART_GROUNDCOMM,MsgBuffer.Checksum);

	return RET_OK;
}

ret_t qComms_ParseByte(Msg_t * msg, uint8_t b){

	static Msg_Parser_State_t state = MSG_STATE_HEADER;
	static unsigned int bytesReaded=0;

	if (msg->Payload == 0x00){
		return RET_ERROR;
	}

	switch (state){
		case MSG_STATE_HEADER:
			if (b==COMMS_HEADER){
				bytesReaded = 0;
				state = MSG_STATE_SOURCE;
				return RET_MSG_BYTES_REMAINING;
			}else{
				return RET_MSG_BYTES_REMAINING;
			}
			break;
		case MSG_STATE_SOURCE:
			msg->SourceAddress = b;
			state = MSG_STATE_DEST;
			return RET_MSG_BYTES_REMAINING;
			break;
		case MSG_STATE_DEST:
			//TODO: Is the package for me?
			msg->DestAddress = b;
			state = MSG_STATE_TIME;
			return RET_MSG_BYTES_REMAINING;
			break;
		case MSG_STATE_TIME:
			//TODO: Is the correct time or seq?
			msg->TimeStamp = b;
			state = MSG_STATE_TYPE;
			return RET_MSG_BYTES_REMAINING;
			break;
		case MSG_STATE_TYPE:
			msg->Type = b;
			state = MSG_STATE_LENGTH;
			return RET_MSG_BYTES_REMAINING;
			break;
		case MSG_STATE_LENGTH:
			msg->Length = b;
			state = MSG_STATE_PAYLOAD;
			return RET_MSG_BYTES_REMAINING;
			break;
		case MSG_STATE_PAYLOAD:
			*(msg->Payload+bytesReaded) = b;
			if ((++bytesReaded)==msg->Length){
				state = MSG_STATE_CHECKSUM;
				return RET_MSG_BYTES_REMAINING;
			}
			break;
		case MSG_STATE_CHECKSUM:
			if ((uint8_t)  (msg->SourceAddress +
							msg->DestAddress +
							msg->TimeStamp +
							msg->Length) == b ){
				//Valid msg
				state = MSG_STATE_HEADER;
				return RET_MSG_OK;
			}else{
				// Invalid msg
				state = MSG_STATE_HEADER;
				return RET_MSG_ERROR;
			}
			break;
	}

	// The state machine always return.
	// This is an error
	return RET_ERROR;
}
