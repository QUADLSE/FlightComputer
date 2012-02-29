
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

void PID_Task(void * pvParameters){

	portTickType xLastWakeTime;

	// Variables globales
	float y, y_old=0.0;
	float error, error_old=0.0;
	float yp, yi, yd, yi_old=0;

	float motor2, motor4;

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

#if 0
		angles.roll = angles.roll + 5.0;

		if (angles.roll > 180.0){
			angles.roll = 0.0;
		}

		angles.pitch = -angles.roll;
		angles.yaw = 165.0;
#endif
	    error = angles.roll-SetPoint;

		// Calculo de los coeficientes P, I, D
		yp = Kp*error;
		yi = yi_old + (Ki*Ts)*error_old;
		yd = (Kd/Ts)*angles.gyroRoll;

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
/*
		if (TLMDelay == 5){
			TLMData.data1 = angles.roll;
			TLMData.data2 = angles.gyroRoll;
			TLMData.data3 = SetPoint;
			TLMData.data4 = motor2;
			TLMData.data5 = motor4;
			TLMData.data6 = y ;
			qComms_SendMsg(UART_GROUND,0xAA,MSG_TYPE_TELEMETRY,sizeof(TLMData),&(TLMData));
		}else{
			TLMDelay++;
		}
*/
		vTaskDelayUntil( &xLastWakeTime, 10/portTICK_RATE_MS );
	}
}
