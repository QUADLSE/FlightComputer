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
#include "qUART.h"
#include "string.h"
#include "comms.h"

const uint8_t buff[]={"Hello world!"};

Msg_t msg;
uint8_t msgBuff[255];

void UART_Rx_Handler(uint8_t * buff, size_t sz){
	int i;

	for (i=0;i<sz;i++){
		switch (qComms_ParseByte(&msg,*(buff+i))){
			case RET_MSG_BYTES_REMAINING:
				break;
			case RET_MSG_ERROR:
				qUART_SendByte(2,'E');
				break;
			case RET_MSG_OK:
				qUART_Send(2,msg.Payload,msg.Length);
				break;
			case RET_ERROR:
				// Problem with memory
				break;
			case RET_OK:
				// Neever
				break;
		}
	}
}

int AppMain(void) {

	//XXX: Should this be done in the comms api?
	qUART[2].BaudRate = 115200;
	qUART[2].DataBits = 8;
	qUART[2].Parity = PARITY_NONE;
	qUART[2].StopBits = 1;

	if (qUART_Init(2)==RET_ERROR){
		while(1);
	};

	qUART_Register_RBR_Callback(UART_Rx_Handler);

	msg.Payload = msgBuff;

	while(1) {
		//int i;
		//qComms_SendMsg(0xBB,MSG_TYPE_DEBUG,strlen((char *)buff),buff);
		//for(i=0;i<500000;i++);
	}
	return 0 ;
}

