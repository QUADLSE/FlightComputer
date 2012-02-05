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

//XXX: Be carefull. This function is being called inside the UART IRQ so it must return quickly.
//TODO: Implement a decoupling system for the data management.
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
			default:
				break;
		}
	}
}

int AppMain(void) {

	//XXX: Should this be done in the comms api?

	if (qUART_Init(2,115200,8,PARITY_NONE,8)==RET_ERROR){
		while(1);
	};

	msg.Payload = msgBuff;
	qUART_Register_RBR_Callback(2, UART_Rx_Handler);
	qComms_SendMsg(0xBB,MSG_TYPE_DEBUG,strlen((char *)buff),buff);

	while(1) {
		//int i;
		//qComms_SendMsg(0xBB,MSG_TYPE_DEBUG,strlen((char *)buff),buff);
		//for(i=0;i<500000;i++);
	}
	return 0 ;
}

