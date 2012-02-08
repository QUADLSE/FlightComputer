/*
 * ESC.h
 *
 *  Created on: 08/02/2012
 *      Author: Administrador
 */

#ifndef ESC_H_
#define ESC_H_

#include <stdint.h>
#include "base.h"
#include "../API_Config.h"


//===========================================================
// Prototypes
//===========================================================

ret_t ESC_Init(uint8_t ESC_ID, uint32_t ESC_FREC_HZ, uint32_t ESC_MIN_DUTY_US, uint32_t ESC_MAX_DUTY_US);
ret_t ESC_DeInit(uint8_t ESC_ID);
ret_t ESC_SetChannel(uint8_t ESC_CHANNEL);
ret_t ESC_DisChannel(uint8_t ESC_CHANNEL);
ret_t ESC_SetSpeed(uint8_t ESC_ID,uint32_t ESC_SPEED);
ret_t ESC_SetDuty(uint8_t ESC_ID, uint32_t ESC_DUTY_US);
uint32_t ESC_GetSpeed(uint8_t ESC_ID);

#endif /* ESC_H_ */
