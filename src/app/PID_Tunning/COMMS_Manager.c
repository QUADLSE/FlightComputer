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
#include "DebugConsole.h"

#include "qFSM.h"
#include "States.h"
#include "Config.h"

void UART_Rx_Handler(uint8_t * buff, size_t sz);
//void ControlDataHandle(void * pvParameters);
//void SystemDataHandle(void * pvParameters);

static Msg_t msg;
static uint8_t msgBuff[255];

char msg_UnhandledMsg[] = {"ERROR. Data type not accepted.\r\n"};
char msg_InvalidMsg[] = {"ERROR: Invalid message received\r\n"};

xQueueHandle ControlQueue;
xQueueHandle SystemQueue;

void COMMS_Init(void){

	msg.Payload = msgBuff;
	qUART_Register_RBR_Callback(UART_GROUND, UART_Rx_Handler);

	// FIXME: What to do with the msg size? ughhh its fixed size, horrible.
	ControlQueue = xQueueCreate(1,sizeof(uint8_t)*20);
	//SystemQueue =  xQueueCreate(1,sizeof(uint8_t)*10);

}

#if 0
void ControlDataHandle(void * pvParameters){
	uint8_t buff[4];
	int i;
	float Kp,Ki,Kd,Bias;
	for (;;){
		//xQueueReceive(ControlQueue,buff,portMAX_DELAY);
		Kp = (float)buff[0]*0.1;
		Ki = (float)buff[1]*0.1;
		Kd = (float)buff[2]*0.1;
		Bias = (float)buff[3]*0.1;
	}
}

void ControlData(uint8_t * data){

	extern float Kp, Ki, Kd, Bias;
	// Read for floats in LittleEndian and save them to Kp, Ki, Kd and Bias repsectivly
	memcpy(&Kp,(data+0),4);
	memcpy(&Ki,(data+4),4);
	memcpy(&Kd,(data+8),4);
	memcpy(&Bias,(data+12),4);
	memcpy(&SetPoint,(data+16),4);
	ConsolePuts("Constants received OK.\r\n",GREEN);

}

#endif

void SystemDataHandle(uint8_t * buff){

	switch(buff[0]-'0'){
		case SYSTEM_MSG_CHANGE_MODE:
			DebugConsolePuts("Chainging to mode: ",BLUE);
			//DebugConsolePuts(stateNames[buff[1]],BLUE);
			DebugConsolePuts(sysStates[buff[1]-'0'].stateName,BLUE);
			qFSM_ChangeState(buff[1]-'0');
			break;
		case SYSTEM_MSG_DEBUG_OFF:
			DebugConsolePuts("Debug console OFF. \r\n",BLUE);
			break;
		case SYSTEM_MSG_DEBUG_ON:
			DebugConsolePuts("Debug console ON. \r\n",BLUE);
			break;
		case SYSTEM_MSG_RESET_IDLE:

			DebugConsolePuts("Resetting system in 3 seconds. \r\n",BLUE);
			qWDT_Start(3000);
			while(1);

			break;
		case SYSTEM_MSG_TLM_OFF:
			DebugConsolePuts("Telemetry OFF. \r\n",BLUE);
			break;
		case SYSTEM_MSG_TLM_ON:
			DebugConsolePuts("Telemetry ON. \r\n",BLUE);
			break;
		default:
			DebugConsolePuts("Invalid SYSTEM_MSG received. \r\n",RED);
	}

}


/* --------------------------------------------------------------------------------------------------------------- */
/* IRQ Handler */
/* --------------------------------------------------------------------------------------------------------------- */
//XXX: Be carefull. This function is being called inside the UART IRQ so it must return quickly.
ret_t r;

void UART_Rx_Handler(uint8_t * buff, size_t sz){

	int i;
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	for (i=0;i<sz;i++){
		r = qComms_ParseByte(&msg,*(buff+i));
		switch (r){
			case RET_MSG_BYTES_REMAINING:
				break;
			case RET_MSG_ERROR:
				ConsolePuts(msg_InvalidMsg,RED);
				break;
			case RET_MSG_OK:
				switch (msg.Type){
					case MSG_TYPE_CONTROL:
						xQueueSendFromISR(ControlQueue,&msg.Payload,&xHigherPriorityTaskWoken);
						//ControlData(msg.Payload);
						break;
					case MSG_TYPE_SYSTEM:
						SystemDataHandle(msg.Payload);
						break;
					default:
						ConsolePuts(msg_UnhandledMsg,RED);
						break;
				}
				break;
			case RET_ERROR:
				// Problem with memory
				break;
			case RET_OK:
				// Neever
				break;
			default:
				while(1);
				break;
		}
	}

	//portEND_SWITCHING_ISR( xHigherPriorityTaskWoken);
}
