/***********************************************************************//**
 * @file		qPWM.h
 * @brief		Contains all macro definitions and function prototypes
 * 				for the PWM driver.
 * @version		1.0
 * @date
 * @author
 *************************************************************************/

/** @ingroup BSP */
/** @addtogroup PWM */
/*@{*/
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

/********************************************************************//**
 * @brief 		qPWM Init function
 * @param[in]	id PWM number (defined in BSP_config.h)
 * @return 		RET_OK If the device was initialized
 * @return 		RET_ERROR If the device couldn't be initialized
 * @return 		RET_DEVICE_ALREADY_INIT If the device was already Initialized. Call qUART_DeInit first.
 *********************************************************************/
ret_t qPWM_Init(uint8_t qPWM_ID);

/********************************************************************//**
 * @brief 		qPWM Deinit
 * @param[in]	id PWM number (defined in BSP_config.h)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qPWM_DeInit(uint8_t qPWM_ID);

/********************************************************************//**
 * @brief 		qPWM Configuration
 * @param[in]	id PWM number (defined in BSP_config.h)
 * @param[in]	PWM frecuency (in Hz)
 * @param[in]	minimum duty (in microseconds)
 * @param[in]	maximum duty (in microseconds)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qPWM_Config(uint8_t qPWM_ID,uint32_t qPWM_FREC_HZ,uint32_t qPWM_MIN_DUTY,uint32_t qPWM_MAX_DUTY);

/********************************************************************//**
 * @brief 		qPWM Channel Init
 * @param[in]	id PWM Channel number
 * @param[in]	Channel edge mode (SINGLE_EDGE or DOUBLE_EDGE)
 * @param[in]	initial duty (in microseconds)
 * @return 		RET_OK, RET_ERROR
 * @return 		RET_DEVICE_ALREADY_INIT If the device was already Initialized. Call qPWM_DisChannel first.
 *********************************************************************/
ret_t qPWM_SetChannel(uint8_t qPWM_CHANNEL, edgemode_t qPWM_EDGE_MODE,uint32_t qPWM_DUTY);

/********************************************************************//**
 * @brief 		qPWM Channel DeInit
 * @param[in]	id PWM Channel number
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qPWM_DisChannel(uint8_t qPWM_CHANNEL);

/********************************************************************//**
 * @brief 		qPWM Channel duty setter
 * @param[in]	id PWM Channel number
 * @param[in]	new PWM duty (in microseconds)
 * @return 		RET_OK, RET_ERROR
 *********************************************************************/
ret_t qPWM_SetPWM(uint8_t qPWM_CHANNEL,uint32_t qPWM_DUTY);

/********************************************************************//**
 * @brief 		qPWM Channel duty getter
 * @param[in]	id PWM Channel number
 * @return 		PWM duty (in microseconds)
 *********************************************************************/
uint32_t qPWM_GetPWM(uint32_t qPWM_CHANNEL);



#endif /* QPWM_H_ */
