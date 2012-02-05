/***********************************************************************//**
 * @file		qUART.h
 * @brief		Contains all macro definitions and function prototypes
 * 				for the UART driver.
 * @version		1.0
 * @date
 * @author
 *************************************************************************/

/** @defgroup UART UART
 * @ingroup BSP Drivers
 * @{
 */

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

/********************************************************************//**
 * @brief 		qUART Init function
 * @param[in]	id UART number (defined in BSP_config.h)
 * @param[in]	BaudRate
 * @param[in]	DataBits
 * @param[in]	Parity
 * @param[in]	StopBits
 * @return 		RET_OK If the device was initialized
 * @return 		RET_ERROR If the device couldn't be initialized
 * @return 		RET_DEVICE_ALREADY_INIT If the device was already Initialized. Call qUART_DeInit first.
 *********************************************************************/
ret_t qUART_Init(uint8_t id, uint32_t BaudRate, uint8_t DataBits, qUART_Parity_t Parity, uint8_t StopBits);

/********************************************************************//**
 * @brief 		qUART Deinit
 * @param[in]	id UART number (defined in BSP_config.h)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qUART_DeInit(uint8_t qUART_ID);

/********************************************************************//**
 * @brief 		Callback register function.
 * 				This function is called every time a new chunk of data is called. Then buffer pointer and size is passed.
 * @param[in]	id UART number (defined in BSP_config.h)
 * @param[in]	pf Pointer to function that handles new data
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qUART_Register_RBR_Callback(uint8_t id, void (*pf)(uint8_t *, size_t sz));

/********************************************************************//**
 * @brief 		qUART Send buffer
 * @param[in]	id UART number (defined in BSP_config.h)
 * @param[in]	buff Pointer to data buffer
 * @param[in]	size Buffer length
 * @return 		Number of bytes sent
 *********************************************************************/
uint32_t qUART_Send(uint8_t qUART_ID, uint8_t * buff, size_t size);

/********************************************************************//**
 * @brief 		qUART Send byte
 * @param[in]	id UART number (defined in BSP_config.h)
 * @param[in]	Byte to be send
 * @return 		None
 *********************************************************************/
ret_t qUART_SendByte(uint8_t qUART_ID, uint8_t ch);

#endif /* qUART_H_ */

/**
 * @}
 */

