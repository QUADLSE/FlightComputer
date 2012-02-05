/*
 * qUART.c
 *
 *  Created on: Feb 1, 2012
 *      Author: Alan
 */

// API Interface
#include "qUART.h"

// Board specific
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"

//===========================================================
// Defines
//===========================================================
#define FIFO_TRIGGER_LEVEL 14

//===========================================================
// Variables
//===========================================================
static LPC_UART_TypeDef * uarts[] = {qUART_0, qUART_1, qUART_2};
static uint8_t RxBuff[FIFO_TRIGGER_LEVEL];

//===========================================================
// Prototypes
//===========================================================

void UART_IntErr(uint8_t bLSErrType);
void UART_IntTransmit(void);
void UART_IntReceive(void);
void (*RBR_Handler)(uint8_t *,size_t sz) = NULL;

//===========================================================
// Functions
//===========================================================

ret_t qUART_Init(uint8_t id){

	PINSEL_CFG_Type PinCfg;
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	int rxPin,txPin,rxPort,txPort,pinFunc;

	// Check if the device wasn't initialized first
	if (qUART[id]._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}

	// Config pins
	if (uarts[id]==LPC_UART0){
		// TODO: Implement
		return RET_ERROR;
	}else if (uarts[id]==LPC_UART2){
		rxPin = PINSEL_PIN_10;
		rxPort = PINSEL_PORT_0;
		txPin = PINSEL_PIN_11;
		txPort = PINSEL_PORT_0;
		pinFunc = 1;
	}else if (uarts[id]==LPC_UART3){
		rxPin = PINSEL_PIN_0;
		rxPort = PINSEL_PORT_0;
		txPin = PINSEL_PIN_1;
		txPort = PINSEL_PORT_0;
		pinFunc = 2;
	}else{
		return RET_ERROR;
	}

	PinCfg.Funcnum = pinFunc;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinCfg.Pinnum = rxPin;
	PinCfg.Portnum = rxPort;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = txPin;
	PinCfg.Portnum = txPort;
	PINSEL_ConfigPin(&PinCfg);

	// Configuramos la UART
	UARTConfigStruct.Baud_rate = qUART[id].BaudRate;
	UARTConfigStruct.Databits = UART_DATABIT_8; 	//FIXME: remove hardcode
	UARTConfigStruct.Parity = UART_PARITY_NONE;		//FIXME: remove hardcode
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;		//FIXME: remove hardcode

	// Inicializamos la UART
	UART_Init(uarts[id], &UARTConfigStruct);

	// -------------------------------------------------------
	// UART FIFOS
	//TODO: Implement the generic handler for using any UART. Consider for any UART.

	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UARTFIFOConfigStruct.FIFO_DMAMode = ENABLE;
	UARTFIFOConfigStruct.FIFO_Level = UART_FIFO_TRGLEV3;
	UART_FIFOConfig(LPC_UART3, &UARTFIFOConfigStruct);

	UART_TxCmd(LPC_UART3, ENABLE);
	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);
	UART_IntConfig(LPC_UART3, UART_INTCFG_RLS, ENABLE);

	NVIC_EnableIRQ (UART3_IRQn);
	// -------------------------------------------------------

	qUART[id]._DeviceStatus = DEVICE_READY;

	return RET_OK;
}

ret_t qUART_DeInit(uint8_t id){
	if (qUART[id]._DeviceStatus == DEVICE_READY){
		UART_DeInit(uarts[id]);
		qUART[id]._DeviceStatus = DEVICE_NOT_READY;
		return RET_OK;
	}else{
		return RET_ERROR;
	}
}

uint32_t qUART_Send(uint8_t id, uint8_t * buff, size_t size){
	if (qUART[id]._DeviceStatus == DEVICE_NOT_READY){
		return RET_ERROR;
	}
	return UART_Send(uarts[id],buff,size,BLOCKING);;
}

ret_t qUART_SendByte(uint8_t id, uint8_t ch){
	if (qUART[id]._DeviceStatus == DEVICE_NOT_READY){
		return RET_ERROR;
	}

	UART_SendByte(uarts[id],ch);

	return RET_OK;
}

//TODO: Implement the generic handler for using any UART. It should be an array of pf
ret_t qUART_Register_RBR_Callback(void (*pf)(uint8_t *, size_t sz)){
	if (pf == NULL){
		return RET_ERROR;
	}
	RBR_Handler = pf;

	return RET_OK;
}


//===========================================================
// Handlers
//===========================================================

//TODO: Implement the generic handler for using DMA with any UART
void UART3_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;
	uint32_t rLen;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(LPC_UART3);
	tmp = intsrc & UART_IIR_INTID_MASK;

	/* Receive Line Status */
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(LPC_UART3);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
			UART_IntErr(tmp1);
		}
	}

	/* Receive Data Available or Character time-out */
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		/*
		 * The FIFO Triggered so read the buffer.
		 * NON BLOCKING IS FUNDAMENTAL. If the IRQ was caused by RDA then, RLen must
		 * be FIFO_TRIGGER_LEVEL. If the IRQ was caused by CTI, then rLen is important
		 */

		rLen = UART_Receive((LPC_UART_TypeDef *)LPC_UART3, (uint8_t *)&RxBuff[0], FIFO_TRIGGER_LEVEL, NONE_BLOCKING);
		(*RBR_Handler)(RxBuff,rLen);
	}

	/* Transmit Holding Empty */
	if (tmp == UART_IIR_INTID_THRE){
		//UART_IntTransmit();
	}
}

/*********************************************************************//**
 * @brief		UART Line Status Error
 * @param[in]	bLSErrType	UART Line Status Error Type
 * @return		None
 **********************************************************************/
void UART_IntErr(uint8_t bLSErrType)
{
	uint8_t test;
	/* Loop forever */
	while (1){
		/* For testing purpose */
		test = bLSErrType;
	}
}
