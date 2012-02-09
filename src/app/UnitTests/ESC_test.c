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
	uint32_t i=0;
	uint32_t speed1=250;
	uint32_t speed2=500;
	uint32_t speed3=750;
	uint32_t speed4=1000;

	ESC_Init(1,50,5000,6000);
	ESC_SetChannel(1);
	ESC_SetChannel(2);
	ESC_SetChannel(3);
	ESC_SetChannel(4);

	while(1)
	{
		ESC_SetSpeed(1,speed1);
		ESC_SetSpeed(2,speed2);
		ESC_SetSpeed(3,speed3);
		ESC_SetSpeed(4,speed4);
		speed1=(speed1+1)%1001;
		speed2=(speed2+1)%1001;
		speed3=(speed3+1)%1001;
		speed4=(speed4+1)%1001;
		for(i=0;i<1000000;i++);
	}

}
