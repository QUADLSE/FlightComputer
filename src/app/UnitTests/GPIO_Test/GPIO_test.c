/*
 * GPIO_test.c
 *
 *  Created on: Feb 9, 2012
 *      Author: Alan
 */

#include "base.h"
#include "qGPIO.h"

void AppMain(void){
	qGPIO_Init(0,qGPIO_OUTPUT);
	qGPIO_Init(1,qGPIO_OUTPUT);
	qGPIO_Init(2,qGPIO_OUTPUT);
	qGPIO_Init(3,qGPIO_OUTPUT);

	qGPIO_Set(0,qGPIO_HIGH);
	qGPIO_Set(0,qGPIO_LOW);

	qGPIO_Set(1,qGPIO_HIGH);
	qGPIO_Set(1,qGPIO_LOW);

	qGPIO_Set(2,qGPIO_HIGH);
	qGPIO_Set(2,qGPIO_LOW);

	qGPIO_Set(3,qGPIO_HIGH);
	qGPIO_Set(3,qGPIO_LOW);

	qGPIO_Set(0,qGPIO_HIGH);
	qGPIO_Set(1,qGPIO_HIGH);
	qGPIO_Set(2,qGPIO_HIGH);
	qGPIO_Set(3,qGPIO_HIGH);

	qGPIO_Set(0,qGPIO_LOW);
	qGPIO_Set(1,qGPIO_LOW);
	qGPIO_Set(2,qGPIO_LOW);
	qGPIO_Set(3,qGPIO_LOW);

}

