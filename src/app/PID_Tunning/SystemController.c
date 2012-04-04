/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : Quadrotor On board computer
===============================================================================
*/

#include "base.h"
#include "qFSM.h"
#include "States.h"
#include "qWDT.h"
#include "DebugConsole.h"
#include "Config.h"



xQueueHandle StatesQueue;

void SystemController(void * pvParameters){

	//State_t State_Reset ={STATE_RESET,NULL,NULL};
	uint8_t newState;

	uint8_t InitialState = (uint8_t) pvParameters;
	systemState = STATE_RESET;

	// Create the system queue
	StatesQueue = xQueueCreate(1,sizeof(uint8_t));

	// Inject the first State
	qFSM_ChangeState(InitialState);

	for (;;){
		// Read for a new state Change, Block Forever if no new states
		xQueueReceive(StatesQueue,&newState,portMAX_DELAY);

		if (systemState == STATE_RESET){
			systemState = newState;
			sysStates[systemState].onEntry(NULL);

			if (qWDT_GetResetSource()==RESET_WDT){

				for (;;){
					qLedsFlash(2,50);
					qWDT_Feed();
				}
			}

			//qWDT_Start(3000);
		}else{
			if (TransitionValid(systemState,newState,transitionTable)==YES){
				DebugConsolePuts("STATE TRANSISTION ",YELLOW);
				DebugConsolePuts(sysStates[systemState].stateName,YELLOW);
				DebugConsolePuts(" -> ",YELLOW);
				DebugConsolePuts(sysStates[newState].stateName,YELLOW);
				DebugConsolePuts(" [OK]\r\n",YELLOW);

				sysStates[systemState].onExit(NULL);
				systemState = newState;
				sysStates[systemState].onEntry(NULL);

			}else{

				DebugConsolePuts("STATE TRANSISTION ",RED);
				DebugConsolePuts(sysStates[systemState].stateName,RED);
				DebugConsolePuts(" -> ",RED);
				DebugConsolePuts(sysStates[newState].stateName,RED);
				DebugConsolePuts(" [ERROR]\r\n",RED);
				while(1);
			}
		}
	}
}

void qFSM_ChangeState(uint8_t nextState){
	xQueueSend(StatesQueue,&nextState,portMAX_DELAY);
}


void AppMain(void) {

	qFSM_registerState(STATE_INIT,"INIT",Init_onEntry,Init_onExit);
	qFSM_registerState(STATE_IDLE,"IDLE",Idle_onEntry,Idle_onExit);
	qFSM_registerState(STATE_FLIGHT_MANUAL,"Flight/Manual",Fligth_Manual_onEntry,Fligth_Manual_onExit);
	xTaskCreate(SystemController, ( signed char * ) "System Controller", 1000, ( void * ) STATE_INIT, 3, NULL );

	vTaskStartScheduler();

	for(;;);
}
