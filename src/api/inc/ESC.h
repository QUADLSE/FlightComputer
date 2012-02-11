/***********************************************************************//**
 * @file		ESC.h
 * @brief		Contains all macro definitions and function prototypes
 * 				for the ESC API.
 * @version		1.0
 * @date
 * @author
 *************************************************************************/


/** @ingroup API */
/** @addtogroup ESC */
/*@{*/

#ifndef ESC_H_
#define ESC_H_

#include <stdint.h>
#include "base.h"
#include "../API_Config.h"


//===========================================================
// Prototypes
//===========================================================

/********************************************************************//**
 * @brief 		ESC Init function
 * @param[in]	id ESC number
 * @param[in]	frecuency (in Hz)
 * @param[in]	ESC minimum duty (in microseconds)
 * @param[in]	ESC maximum duty (in microseconds)
 * @return 		RET_OK If the device was initialized
 * @return 		RET_ERROR If the device couldn't be initialized
 * @return 		RET_DEVICE_ALREADY_INIT If the device was already Initialized. Call ESC_DeInit first.
 *********************************************************************/
ret_t ESC_Init(uint8_t ESC_ID, uint32_t ESC_FREC_HZ, uint32_t ESC_MIN_DUTY_US, uint32_t ESC_MAX_DUTY_US);

/********************************************************************//**
 * @brief 		ESC Deinit
 * @param[in]	id ESC number (defined in BSP_config.h)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t ESC_DeInit(uint8_t ESC_ID);

/********************************************************************//**
 * @brief 		ESC Channel Init function
 * @param[in]	id ESC number
 * @param[in]	frecuency (in Hz)
 * @return 		RET_OK If the device was initialized
 * @return 		RET_ERROR If the device couldn't be initialized
 * @return 		RET_DEVICE_ALREADY_INIT If the device was already Initialized. Call ESC_DeInit first.
 *********************************************************************/
ret_t ESC_SetChannel(uint8_t ESC_CHANNEL);

/********************************************************************//**
 * @brief 		ESC Channel Deinit
 * @param[in]	id ESC number (defined in BSP_config.h)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t ESC_DisChannel(uint8_t ESC_CHANNEL);

/********************************************************************//**
 * @brief 		ESC Channel speed setter
 * @param[in]	id ESC Channel number
 * @param[in]	new ESC speed (0-1000 absolute ESC speed)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t ESC_SetSpeed(uint8_t ESC_ID,uint32_t ESC_SPEED);

/********************************************************************//**
 * @brief 		ESC Channel duty setter
 * @param[in]	id ESC Channel number
 * @param[in]	new ESC duty (in microseconds, must match maximum and minimum configurations)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t ESC_SetDuty(uint8_t ESC_ID, uint32_t ESC_DUTY_US);

/********************************************************************//**
 * @brief 		qPWM Channel duty getter
 * @param[in]	id PWM Channel number
 * @return 		PWM duty (in microseconds)
 *********************************************************************/
uint32_t ESC_GetSpeed(uint8_t ESC_ID);

#endif /* ESC_H_ */
