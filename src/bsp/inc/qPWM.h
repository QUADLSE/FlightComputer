/*
 * qPWM.h
 *
 *  Created on: 02/02/2012
 *      Author: Administrador
 */

#ifndef QPWM_H_
#define QPWM_H_

#include <stdint.h>

#include "base.h"
#include "BSP_Config.h"



//===========================================================
// Types
//===========================================================
typedef enum{
	SINGLE_EDGE,
	DOUBLE_EDGE
} edgemode_t;

typedef struct{
	uint32_t Frec;
	uint32_t MinDuty;
	uint32_t MaxDuty;
	status_t _DeviceStatus;
} qPWM_t;

typedef struct{
	edgemode_t EdgeMode;
	uint32_t Duty;
	status_t _DeviceStatus;
} qPWMChannel_t;

//===========================================================
// Externs
//===========================================================
extern qPWMChannel_t qPWM_CHANNEL[qPWM_CHANNELS];
extern qPWM_t qPWM;
//===========================================================
// Prototypes
//===========================================================
ret_t qPWM_Init(uint8_t qPWM_ID);
ret_t qPWM_DeInit(uint8_t qPWM_ID);
ret_t qPWM_Config(uint8_t qPWM_ID,uint32_t qPWM_FREC_HZ,uint32_t qPWM_MIN_DUTY,uint32_t qPWM_MAX_DUTY);
ret_t qPWM_SetChannel(uint8_t qPWM_CHANNEL, edgemode_t qPWM_EDGE_MODE,uint32_t qPWM_DUTY);
ret_t qPWM_DisChannel(uint8_t qPWM_CHANNEL);
ret_t qPWM_SetPWM(uint8_t qPWM_CHANNEL,uint32_t qPWM_DUTY);
uint32_t qPWM_GetPWM(uint32_t qPWM_CHANNEL);



#endif /* QPWM_H_ */
