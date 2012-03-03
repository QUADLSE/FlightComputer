
#include "FreeRTOS.h"
#include "task.h"

#include "qIMU.h"
#include "qCOMMS.h"
#include "ESC.h"


const float Ts = 0.010f;
const float UpperLimit = 900.0;
const float LowerLimit = 0.0;

#define MOTOR_1		3
#define MOTOR_2		4
#define MOTOR_3		2
#define MOTOR_4		1

float Kp,Ki,Kd,Bias,SetPoint;

typedef struct{
	float data1;
	float data2;
	float data3;
	float data4;
	float data5;
	float data6;
}TelemetryData;

TelemetryData TLMData;

int TLMDelay = 0;



void PID_13(float angle,float derivate,  float setPoint){

	// Variables globales
	static float y=0.0;
	static float y_old=0.0;
	static float error= 0;
	static float yp, yi, yd;
	static float motor2, motor4;
	static float error_old=0.0;
	static float yi_old=0;

	error = angle-SetPoint;

	// Calculo de los coeficientes P, I, D
	yp = Kp*error;
	yi = yi_old + (Ki*Ts)*error_old;
	yd = -(Kd/Ts)*derivate;

	// La salida se compone de la suma de los tres coeficientes
	y = yi + yp + yd;

	// Guardo los estados como viejos
	y_old = y;

	// en Y tengo la salida
	if ((Bias + y) > UpperLimit){
		yi = yi_old;
	}

	if ((Bias-y) < LowerLimit){
		yi  = yi_old;
	}

	yi_old = yi;
	error_old = error;

	motor2 = Bias + y;
	motor4 = Bias - y;

	ESC_SetSpeed(MOTOR_1,motor2);
	ESC_SetSpeed(MOTOR_3,motor4);
}

void PID_24(float angle, float derivate,  float setPoint){

	// Variables globales
	static float y_old=0.0;
	static float y=0.0;
	static float error= 0;
	static float yp, yi, yd;
	static float motor2, motor4;
	static float error_old=0.0;
	static float yi_old=0;

	error = angle-SetPoint;

	// Calculo de los coeficientes P, I, D
	yp = Kp*error;
	yi = yi_old + (Ki*Ts)*error_old;
	yd = -(Kd/Ts)*derivate;

	// La salida se compone de la suma de los tres coeficientes
	y = yi + yp + yd;

	// Guardo los estados como viejos
	y_old = y;

	// en Y tengo la salida
	if ((Bias + y) > UpperLimit){
		yi = yi_old;
	}

	if ((Bias-y) < LowerLimit){
		yi  = yi_old;
	}

	yi_old = yi;
	error_old = error;

	motor2 = Bias + y;
	motor4 = Bias - y;

	ESC_SetSpeed(MOTOR_4,motor2);
	ESC_SetSpeed(MOTOR_2,motor4);

}

void PID_Task(void * pvParameters){

	portTickType xLastWakeTime;

	// Variables auxiliares
	int i;
	uint8_t buff;

	qIMU_tDataProcessed angles;

	Kp = 0.0;
	Ki = 0.0;
	Kd = 0.0;
	Bias = 0.0;
	SetPoint = 0.0;
	xLastWakeTime = xTaskGetTickCount ();

	angles.roll = 0.0;
	angles.pitch = 90.0;
	angles.gyroPitch = 5.0;
	angles.gyroRoll = 10.0;
	angles.gyroYaw = 15.0;

	for(;;){

		qIMU_ReadProcessed(&angles);
/*
		ESC_SetSpeed(MOTOR_4,Bias);
		ESC_SetSpeed(MOTOR_2,Bias);
		ESC_SetSpeed(MOTOR_1,Bias);
		ESC_SetSpeed(MOTOR_3,Bias);
*/
		PID_13(angles.pitch,-angles.gyroPitch,0.0);
		PID_24(angles.roll,angles.gyroRoll,0.0);

	    vTaskDelayUntil( &xLastWakeTime, 10/portTICK_RATE_MS );
	}
}

