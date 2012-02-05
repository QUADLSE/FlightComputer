#ifndef qUART_H_
#define qUART_H_

#include <stdint.h>

#include "base.h"
#include "BSP_Config.h"

//===========================================================
// Types
//===========================================================
typedef enum{
	PARITY_NONE,
	PARITY_ODD,
	PARITY_EVEN
} qUART_Parity_t;

//===========================================================
// Externs
//===========================================================
extern status_t qUARTStatus[qUART_TOTAL];

//===========================================================
// Prototypes
//===========================================================
ret_t qUART_Init(uint8_t id, uint32_t BaudRate, uint8_t DataBits, qUART_Parity_t Parity, uint8_t StopBits);
ret_t qUART_DeInit(uint8_t qUART_ID);
ret_t qUART_Register_RBR_Callback(uint8_t id, void (*pf)(uint8_t *, size_t sz));

uint32_t qUART_Send(uint8_t qUART_ID, uint8_t * buff, size_t size);
ret_t qUART_SendByte(uint8_t qUART_ID, uint8_t ch);

#endif /* qUART_H_ */
