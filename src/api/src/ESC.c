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




ret_t ESC_Init(uint8_t ESC_ID, uint32_t ESC_FREC_HZ, uint32_t ESC_MINDUTY_US, uint32_t ESC_MAXDUTY_US)
{
	//Verifico que no este iniciado el ESC
	if(qPWM._DeviceStatus==DEVICE_READY){
		return RET_ALREADY_INIT;
	}

	qPWM_Init(ESC_ID);
	qPWM_Config(ESC_ID, ESC_FREC_HZ, ESC_MINDUTY_US, ESC_MAXDUTY_US);

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
	uint32_t i;
	if(qPWM_CHANNEL[id-1]._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}

	//Inicio el canal en el minimo duty
	if(qPWM_SetChannel(id, SINGLE_EDGE, qPWM.MinDuty)==RET_OK){
		//FIXME: Remove delay
		//Cuando el programa ejecuta sin delay el PWM no funciona, pero haciendo paso a paso con el debbug
		for(i = 0 ; i<1000000 ; i++) ;
		ESC_SetDuty(id,qPWM.MinDuty);
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
	uint32_t duty = qPWM.MinDuty + ((qPWM.MaxDuty - qPWM.MinDuty)*speed/1000);
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
