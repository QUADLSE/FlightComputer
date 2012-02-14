/*
 * PID.c
 *
 *  Created on: Feb 14, 2012
 *      Author: Alan
 */

#include "FreeRTOS.h"
#include "task.h"

#include "qIMU.h";

float Kp,Ki,Kd,Bias;
const float Ts = 0.100f;

void PID_Task(void * pvParameters){

	portTickType xLastWakeTime;
	const portTickType xFrequency = 10;

	// Variables globales
	float y, y_old=0.0;
	float error, error_old=0.0;
	float yp, yi, yd, yi_old=0;

	// Variables auxiliares
	int i;
	uint8_t buff;

	qIMU_tDataProcessed angles;

	Kp = 0.0;
	Ki = 0.0;
	Kd = 0.0;
	Bias = 0.0;
	xLastWakeTime = xTaskGetTickCount ();

	for(;;){

		// En error entra el dato
		//errror = ang_medido - ang_deseado;
		qIMU_ReadProcessed(&angles);

	    error = (float)angles.pitch/100.0;

		// Calculo de los coeficientes P, I, D
		yp = Kp*error;
		yi = yi_old + (Ki*Ts)*error_old;
		yd = (Kd/Ts)*(error-error_old);

		// La salida se compone de la suma de los tres coeficientes
		y = yi + yp + yd;

		// Guardo los estados como viejos
		y_old = y;
		yi_old = yi;
		error_old = error;

		// en Y tengo la salida

		vTaskDelayUntil( &xLastWakeTime, 10/portTICK_RATE_MS );
	}
}
