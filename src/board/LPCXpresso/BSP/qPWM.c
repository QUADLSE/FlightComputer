/*
 * qPWM.c
 *
 *  Created on: 06/02/2012
 *      Author: Administrador
 */

// API Interface
#include "qPWM.h"

// Board specific
#include "lpc17xx_pwm.h"
#include "lpc17xx_pinsel.h"

ret_t qPWM_Init(uint8_t id)
{
	//TODO: Implementar para una cantidad generica de PWMs
	if(qPWM._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}

	PWM_TIMERCFG_Type PWMCfgDat;
	/* PWM block section -------------------------------------------- */
	/* Initialize PWM peripheral, timer mode
	 * PWM prescale value = 1 (absolute value - tick value) */
	PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;
	PWMCfgDat.PrescaleValue = 1;
	PWM_Init(qPWM_1, PWM_MODE_TIMER, (void *) &PWMCfgDat);

	qPWM._DeviceStatus=DEVICE_READY;

	return RET_OK;
}

ret_t qPWM_DeInit(uint8_t id){
	if (qPWM._DeviceStatus == DEVICE_READY){
		PWM_DeInit(qPWM_1);
		qPWM._DeviceStatus = DEVICE_NOT_READY;
		return RET_OK;
	}else{
		return RET_ERROR;
	}
}

ret_t qPWM_Config(uint8_t qPWM_ID, uint32_t qPWM_FREC,uint32_t qPWM_MIN_DUTY,uint32_t qPWM_MAX_DUTY)
{
	if(qPWM._DeviceStatus==DEVICE_NOT_READY){
		return RET_ERROR;
	}

	if(qPWM_MIN_DUTY>qPWM_MAX_DUTY){
		return RET_ERROR;
	}

	qPWM.MinDuty=qPWM_MIN_DUTY;
	qPWM.MaxDuty=qPWM_MAX_DUTY;
	qPWM.Frec=qPWM_FREC;

	PWM_MATCHCFG_Type PWMMatchCfgDat;
	/* Set match value for PWM match channel 0 = 1000, update immediately */
	PWM_MatchUpdate(qPWM_1, 0, 1000000/qPWM_FREC, PWM_MATCH_UPDATE_NOW);
	/* PWM Timer/Counter will be reset when channel 0 matching
	 * no interrupt when match
	 * no stop when match */
	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = 0;
	PWMMatchCfgDat.ResetOnMatch = ENABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(qPWM_1, &PWMMatchCfgDat);

	return RET_OK;

}
ret_t qPWM_SetChannel(uint8_t id, edgemode_t qPWM_EDGE_MODE,uint32_t qPWM_DUTY)
{
	//Check PWM readiness
	if(qPWM._DeviceStatus==DEVICE_NOT_READY){
		return RET_ERROR;
	}
	//Check channel readiness
	if(qPWM_CHANNEL[id]._DeviceStatus==DEVICE_READY){
		return RET_ERROR;
	}


	PINSEL_CFG_Type PinCfg;
	PWM_MATCHCFG_Type PWMMatchCfgDat;

	//Set up pin configuration
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = id;
	PINSEL_ConfigPin(&PinCfg);

	//Set up the the channel
	if(qPWM_EDGE_MODE==DOUBLE_EDGE){
		PWM_ChannelConfig(qPWM_1, id+1, PWM_CHANNEL_DUAL_EDGE);
	} else if(qPWM_EDGE_MODE==SINGLE_EDGE){
		PWM_ChannelConfig(qPWM_1, id+1, PWM_CHANNEL_SINGLE_EDGE);
	}

	//Set up channel's duty
	//PWM_MatchUpdate(qPWM_1, id+1, qPWM_DUTY, PWM_MATCH_UPDATE_NEXT_RST);
	qPWM_SetPWM(id,qPWM_DUTY);

	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = id+1;
	PWMMatchCfgDat.ResetOnMatch = DISABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(qPWM_1, &PWMMatchCfgDat);

	//Enable channel
	PWM_ChannelCmd(qPWM_1, id+1, ENABLE);

	//Reset and counter
	PWM_ResetCounter(qPWM_1);
	PWM_CounterCmd(qPWM_1, ENABLE);

	// Start PWM
	PWM_Cmd(qPWM_1, ENABLE);

	qPWM_CHANNEL[id]._DeviceStatus=DEVICE_READY;
	return RET_OK;

}
ret_t qPWM_DisChannel(uint8_t id)
{
	if(qPWM_CHANNEL[id]._DeviceStatus==DEVICE_READY){
		PWM_ChannelCmd(qPWM_1, id+1, DISABLE);
		qPWM_CHANNEL[id]._DeviceStatus=DEVICE_NOT_READY;
		return RET_OK;
	} else {
		return RET_ERROR;
	}
}
ret_t qPWM_SetPWM(uint8_t id,uint32_t qPWM_DUTY)
{
	if(qPWM_CHANNEL[id]._DeviceStatus==DEVICE_NOT_READY){
		return RET_ERROR;
	}

	if(qPWM_DUTY<qPWM.MinDuty || qPWM_DUTY>qPWM.MaxDuty){
		return RET_ERROR;
	}

	PWM_MatchUpdate(qPWM_1, id+1, qPWM_DUTY, PWM_MATCH_UPDATE_NEXT_RST);

	return RET_OK;

}
uint32_t qPWM_GetPWM(uint32_t id)
{
	if(qPWM_CHANNEL[id]._DeviceStatus==DEVICE_NOT_READY){
			return RET_ERROR;
	}
	return qPWM_CHANNEL[id].Duty;
}

