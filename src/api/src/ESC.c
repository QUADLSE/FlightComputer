/*
 * ESC.c
 *
 *  Created on: 08/02/2012
 *      Author: Administrador
 */

#include <stdint.h>
#include "base.h"
#include "ESC.h"
#include "qPWM.h"




ret_t ESC_Init(uint8_t id, uint32_t frec, uint32_t minduty, uint32_t maxduty)
{
	//Verifico que no este iniciado el ESC
	if(qPWM._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}

	qPWM_Init(id);
	qPWM_Config(id, frec, minduty, maxduty);

	return RET_OK;
}

ret_t ESC_DeInit(uint8_t id)
{
	if(qPWM_DeInit(id)==RET_OK){
		return RET_OK;
	} else {
		return RET_ERROR;
	}
}

ret_t ESC_SetChannel(uint8_t id)
{
	if(qPWM_CHANNEL[id-1]._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}

	//Inicio el canal en el minimo duty
	if(qPWM_SetChannel(id, SINGLE_EDGE, qPWM.MinDuty)==RET_OK){
		return RET_OK;
	} else{
		return RET_ERROR;
	}

}

ret_t ESC_DisChannel(uint8_t id)
{
	if(qPWM_DisChannel(id)==RET_OK){
		return RET_OK;
	} else{
		return RET_ERROR;
	}
}


ret_t ESC_SetSpeed(uint8_t id,uint32_t speed)
{
	//FIXME: Checkear la aritmetica
	uint32_t duty = (qPWM.MaxDuty - qPWM.MinDuty)*speed/1000;
	if(ESC_SetDuty(id,duty)==RET_OK){
		return RET_OK;
	}else{
		return RET_ERROR;
	}
}

ret_t ESC_SetDuty(uint8_t id, uint32_t duty)
{
	if(qPWM_SetPWM(id, duty)==RET_OK){
		return RET_OK;
	}else {
		return RET_ERROR;
	}
}

uint32_t ESC_GetSpeed(uint8_t id)
{
	return qPWM_GetPWM(id);
}
