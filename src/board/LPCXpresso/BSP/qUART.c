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
#define BUFF_SIZE	38

//===========================================================
// Variables
//===========================================================
static LPC_UART_TypeDef * uarts[] = {qUART_0, qUART_1, qUART_2};
uint8_t rxBuff[2][BUFF_SIZE];
static int selectedRxBuff = 0;
GPDMA_Channel_CFG_Type GPDMACfg_rx[2];

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

	//TODO: Implement the generic handler for using any UART. Consider for any UART.

	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UARTFIFOConfigStruct.FIFO_DMAMode = ENABLE;
	//UARTFIFOConfigStruct.FIFO_Level = UART_FIFO_TRGLEV3; //XXX: is this important?
	UART_FIFOConfig(LPC_UART3, &UARTFIFOConfigStruct);

	UART_TxCmd(LPC_UART3, ENABLE);

	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);

	// GPDMA Interrupt configuration section

	GPDMA_Init();

	NVIC_DisableIRQ (DMA_IRQn);
	// preemption = 1, sub-priority = 1
	NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));

	GPDMACfg_rx[0].ChannelNum = 1;
	GPDMACfg_rx[0].SrcMemAddr = 0;
	GPDMACfg_rx[0].DstMemAddr = (uint32_t) rxBuff[0];
	GPDMACfg_rx[0].TransferSize = BUFF_SIZE;
	GPDMACfg_rx[0].TransferWidth = 0;
	GPDMACfg_rx[0].TransferType = GPDMA_TRANSFERTYPE_P2M;
	GPDMACfg_rx[0].SrcConn = GPDMA_CONN_UART3_Rx;
	GPDMACfg_rx[0].DstConn = 0;
	GPDMACfg_rx[0].DMALLI = 0;

	GPDMACfg_rx[1].ChannelNum = 1;
	GPDMACfg_rx[1].SrcMemAddr = 0;
	GPDMACfg_rx[1].DstMemAddr = (uint32_t) rxBuff[1];
	GPDMACfg_rx[1].TransferSize = BUFF_SIZE;
	GPDMACfg_rx[1].TransferWidth = 0;
	GPDMACfg_rx[1].TransferType = GPDMA_TRANSFERTYPE_P2M;
	GPDMACfg_rx[1].SrcConn = GPDMA_CONN_UART3_Rx;
	GPDMACfg_rx[1].DstConn = 0;
	GPDMACfg_rx[1].DMALLI = 0;

	NVIC_EnableIRQ (DMA_IRQn);

	// Selecciono los buffers
	selectedRxBuff = 0;
	GPDMA_Setup(&GPDMACfg_rx[selectedRxBuff]);
	GPDMA_ChannelCmd(1, ENABLE);

	//uint8_t selectedTxBuff = 0;
	//GPDMA_ChannelCmd(0, DISABLE);


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
void DMA_IRQHandler (void)
{
	uint32_t tmp;
	// Scan interrupt pending
	for (tmp = 0; tmp <= 7; tmp++) {
		if (GPDMA_IntGetStatus(GPDMA_STAT_INT, tmp)){
			// Check counter terminal status
			if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, tmp)){
				// Clear terminate counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, tmp);

				switch (tmp){
					case 1:
						GPDMA_ChannelCmd(1, DISABLE);
						if (selectedRxBuff==1){
							selectedRxBuff = 0;
						}else{
							selectedRxBuff = 1;
						}
						GPDMA_Setup(&GPDMACfg_rx[selectedRxBuff]);
						GPDMA_ChannelCmd(1, ENABLE);
						if (selectedRxBuff == 0){
							RBR_Handler(rxBuff[1],BUFF_SIZE);
						}else{
							RBR_Handler(rxBuff[0],BUFF_SIZE);
						}

						break;
					default:
						break;
				}

			}
			// Check error terminal status
			if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, tmp)){
				// Clear error counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, tmp);
				switch (tmp){
				case 1:
					GPDMA_ChannelCmd(1, DISABLE);
					while(1);
					break;
				default:
					break;
				}
			}
		}
	}
}

