/*
 * Comms.c
 *
 *  Created on: Feb 6, 2012
 *      Author: Alan
 *
 */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

#include "qUART.h"
#include "qCOMMS.h"
#include "ESC.h"
#include "string.h"

void UART_Rx_Handler(uint8_t * buff, size_t sz);
void ControlDataHandle(void * pvParameters);
void SystemDataHandle(void * pvParameters);

static Msg_t msg;
static uint8_t msgBuff[255];

xQueueHandle ControlQueue;
xQueueHandle SystemQueue;

extern float Kp,Ki,Kd,Bias;

char helloMsg[]={"QUADLSE V1.0 Initialized..."};

void Communications(void * pvParameters){

	//XXX: Should this be done in the comms api?
	if (qUART_Init(0,115200,8,QUART_PARITY_NONE,8)==RET_ERROR){
		while(1);
	}

	msg.Payload = msgBuff;
	qUART_Register_RBR_Callback(0, UART_Rx_Handler);

	ControlQueue = xQueueCreate(10,sizeof(uint8_t)*4);
	//SystemQueue =  xQueueCreate(10,sizeof(uint8_t)*2);

	qComms_SendMsg(0,0xAA,MSG_TYPE_DEBUG,strlen(helloMsg),helloMsg);

	//xTaskCreate( ControlDataHandle, ( signed char * ) "COMMS/CONTROL", 500, ( void * ) NULL, 2, NULL );
	//xTaskCreate( SystemDataHandle, ( signed char * ) "COMMS/SYSTEM", 500, ( void * ) NULL, 2, NULL );
	vTaskDelete(NULL);
}
#if 0
void ControlDataHandle(void * pvParameters){
	uint8_t buff[4];
	int i;

	for (;;){
		xQueueReceive(ControlQueue,buff,portMAX_DELAY);
		Kp = (float)buff[0]*0.1;
		Ki = (float)buff[1]*0.1;
		Kd = (float)buff[2]*0.1;
		Bias = (float)buff[3]*0.1;
	}
}

void SystemDataHandle(void * pvParameters){
	uint8_t buff[2];
	for (;;){
		xQueueReceive(ControlQueue,buff,portMAX_DELAY);
		//qUART_Send(2,buff,strlen((char*)buff));
	}
}
#endif

/* --------------------------------------------------------------------------------------------------------------- */
/* IRQ Handler */
/* --------------------------------------------------------------------------------------------------------------- */
//XXX: Be carefull. This function is being called inside the UART IRQ so it must return quickly.
void UART_Rx_Handler(uint8_t * buff, size_t sz){

	int i;
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	//char buf[]={"OK\n"};

	for (i=0;i<sz;i++){
		ret_t r = qComms_ParseByte(&msg,*(buff+i));
		switch (r){
			case RET_MSG_BYTES_REMAINING:
				break;
			case RET_MSG_ERROR:
				break;
			case RET_MSG_OK:
				switch (msg.Type){
					case MSG_TYPE_CONTROL:
						//qUART_Send(0,buf,strlen(buf));
						//xQueueSendFromISR(ControlQueue,msg.Payload,&xHigherPriorityTaskWoken);
						//Kp = (float)msg.Payload[0]*0.1;
						//Ki = (float)msg.Payload[1]*0.1;
						//Kd = (float)msg.Payload[2]*0.1;
						//Bias = (float)msg.Payload[3]*0.1;

						break;
					case MSG_TYPE_SYSTEM:
						//xQueueSendFromISR(SystemQueue,msg.Payload,&xHigherPriorityTaskWoken);
						break;
					default:
						break;
				}
				break;
			case RET_ERROR:
				// Problem with memory
				break;
			case RET_OK:
				// Neever
				break;
		}
	}

	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken);
}
