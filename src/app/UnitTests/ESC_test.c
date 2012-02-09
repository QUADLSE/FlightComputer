/*
 * ESC_test.c
 *
 *  Created on: 09/02/2012
 *      Author: Administrador
 */

#include "base.h"
#include "ESC.h"

void ESC_test()
{
	if(ESC_Init(1,50,5000,6000)==RET_OK){
		if(ESC_SetChannel(1)==RET_OK){
			if(ESC_SetSpeed(1,500)==RET_OK){
				;
			}
		}
	}

}
