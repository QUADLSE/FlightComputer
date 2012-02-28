
#include "FreeRTOS.h"
#include "task.h"

#include "qIMU.h"
#include "qCOMMS.h"
#include "ESC.h"


const float Ts = 0.010f;
const float UpperLimit = 500.0;
const float LowerLimit = 0.0;

#define MOTOR_1		3
#define MOTOR_2		4
#define MOTOR_3		2
#define MOTOR_4		1

void PID_Task(void * pvParameters){

	portTickType xLastWakeTime;

	// Variables globales
	float y, y_old=0.0;
	float error, error_old=0.0;
	float yp, yi, yd, yi_old=0;

	float motor2, motor4;

	float Kp,Ki,Kd,Bias,SetPoint;

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

//		qIMU_ReadProcessed(&angles);

		angles.roll = angles.roll + 5.0;

		if (angles.roll > 180.0){
			angles.roll = 0.0;
		}

		angles.pitch = -angles.roll;
		angles.yaw = 165.0;

	    error = angles.roll-SetPoint;

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
		motor2 = Bias + y;
		motor4 = Bias - y;

		if (motor2<LowerLimit){
			motor2 = LowerLimit;
		}

		if (motor2>UpperLimit){
			motor2 = UpperLimit;
		}

		if (motor4<LowerLimit){
			motor4 = LowerLimit;
		}

		if (motor4>UpperLimit){
			motor4 = UpperLimit;
		}

		ESC_SetSpeed(MOTOR_4,motor2);
		ESC_SetSpeed(MOTOR_2,motor4);

		qComms_SendMsg(UART_GROUND,0xAA,MSG_TYPE_TELEMETRY,sizeof(angles),&(angles));

		vTaskDelayUntil( &xLastWakeTime, 20/portTICK_RATE_MS );
	}
}
