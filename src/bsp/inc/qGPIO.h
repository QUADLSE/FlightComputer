/*
 * qGPIO.h
 *
 *  Created on: Feb 8, 2012
 *      Author: Alan
 */

#ifndef QGPIO_H_
#define QGPIO_H_
#include <stdint.h>

#include "base.h"
#include "BSP_Config.h"

//===========================================================
// Types
//===========================================================

typedef enum{
	qGPIO_OUTPUT,
	qGPIO_INPUT
}qGPIO_Direction;

typedef enum{
	qGPIO_HIGH,
	qGPIO_LOW
}qGPIO_Value;

typedef struct{
	qGPIO_Direction dir;
	qGPIO_Value value;
}qGPIO_Pin;

//===========================================================
// Externs
//===========================================================
extern qGPIO_Pin qGPIO[qGPIO_TOTAL];

//===========================================================
// Prototypes
//===========================================================
ret_t qGPIO_Init(int pin, qGPIO_Direction dir);
ret_t qGPIO_DeInit(int pin);
ret_t qGPIO_Set(int pin, qGPIO_Value val);
qGPIO_Value qGPIO_Read(int pin);

#endif /* QGPIO_H_ */
