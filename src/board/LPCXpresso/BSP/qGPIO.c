/*
 * qGPIO.c
 *
 *  Created on: Feb 9, 2012
 *      Author: Alan
 */

#include "qGPIO.h"
#include "lpc17xx_gpio.h"

static uint32_t gpio_pin[] = {qGPIO_PIN0_PIN,qGPIO_PIN1_PIN,qGPIO_PIN2_PIN,qGPIO_PIN3_PIN};
static uint32_t gpio_port[] = {qGPIO_PIN0_PORT,qGPIO_PIN1_PORT,qGPIO_PIN2_PORT,qGPIO_PIN3_PORT};


ret_t qGPIO_Init(int pin, qGPIO_Direction dir){
	GPIO_SetDir(gpio_port[pin],(1<<gpio_pin[pin]),(dir==qGPIO_INPUT)?0:1);
	return RET_OK;
}

ret_t qGPIO_DeInit(int pin){
	GPIO_SetDir(gpio_port[pin],(1<<gpio_pin[pin]),0);
	return RET_OK;
}

ret_t qGPIO_Set(int pin, qGPIO_Value val){
	if (val==qGPIO_HIGH){
		GPIO_SetValue(gpio_port[pin],(1<<gpio_pin[pin]));
	}else if (val==qGPIO_LOW){
		GPIO_ClearValue(gpio_port[pin],(1<<gpio_pin[pin]));
	}else{
		return RET_ERROR;
	}
	return RET_OK;
}

qGPIO_Value qGPIO_Read(int pin){
	if ((GPIO_ReadValue(gpio_port[pin])&(1<<gpio_pin[pin]))!=0){
		return qGPIO_HIGH;
	}else{
		return qGPIO_LOW;
	}
}
