/*
 * qPWM.c
 *
 *  Created on: 02/02/2012
 *      Author: Administrador
 */

#include "qPWM.h"

qPWMChannel_t qPWM_CHANNEL[qPWM_CHANNELS]={{SINGLE_EDGE,0,DEVICE_NOT_READY},{SINGLE_EDGE,0,DEVICE_NOT_READY},{SINGLE_EDGE,0,DEVICE_NOT_READY},{SINGLE_EDGE,0,DEVICE_NOT_READY},{SINGLE_EDGE,0,DEVICE_NOT_READY},{SINGLE_EDGE,0,DEVICE_NOT_READY}};

qPWM_t qPWM={1000,0,1000,DEVICE_NOT_READY};