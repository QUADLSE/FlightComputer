/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#include "base.h"
#include "qPWM.h"

#define PWMMAXDUTY 6000
#define PWMMINDUTY 0

void AppMain(void) {
	//FIXME: Metodo!!!

	uint8_t pwmid=1;
	uint32_t frec=50;
	uint32_t duty=5000;
	uint32_t i=0;


	if(qPWM_Init(pwmid)==RET_OK){
		if(qPWM_Config(pwmid,frec,PWMMINDUTY,PWMMAXDUTY)==RET_OK){
			if(qPWM_SetChannel(1, SINGLE_EDGE,duty)==RET_OK){
				if(qPWM_SetChannel(2, SINGLE_EDGE,duty)==RET_OK){
					if(qPWM_SetChannel(3, SINGLE_EDGE,duty)==RET_OK){
						if(qPWM_SetChannel(4, SINGLE_EDGE,duty)==RET_OK){
							while(qPWM_SetPWM(pwmid,duty)==RET_OK){
								i++;
							}
						}
					}
				}
			}
		}
	}


	return 0 ;
}
