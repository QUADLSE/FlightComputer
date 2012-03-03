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
#include "tasks/tasklist.h"
#include "qFSM.h"

#include "DebugConsole.h"

const transition_t	/* 				  |	STATE_INIT  | STATE_IDLE  |	STATE_FLIGHT_MANUAL	|	STATE_FLIGHT_TUNNING 	|	STATE_FLIGHT_RUNNING |*/
			 transitionTable[5][5]={
/*				STATE_INIT			*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*				STATE_IDLE			*/{		NO,					NO,					YES,					YES,					 	YES				}	,
/*				STATE_FLIGHT_MANUAL	*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*				STATE_FLIGHT_TUNNING*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*				STATE_FLIGHT_RUNNING*/{		NO,					YES,				NO,						NO,					 		NO				}	};

State_t * systemState;;
xQueueHandle StatesQueue;

void ChangeState(State_t * nextState){
	xQueueSend(StatesQueue,&nextState,portMAX_DELAY);
}

void SystemController(void * pvParameters){

	State_t State_Reset ={STATE_RESET,NULL,NULL};
	State_t * newState;

	State_t * InitialState = (State_t *) pvParameters;
	systemState = &State_Reset;

	// Create the system queue
	StatesQueue = xQueueCreate(1,sizeof(State_t * ));

	// Inject the first State
	ChangeState(InitialState);

	for (;;){
		// Read for a new state Change, Block Forever if no new states
		xQueueReceive(StatesQueue,&newState,portMAX_DELAY);

		if (systemState->name == STATE_RESET){
			systemState = newState;
			systemState->onEntry(NULL);
		}else{
			if (TransitionValid(systemState->name,newState->name,transitionTable)==YES){
				ConsolePuts("STATE TRANSISTION ",YELLOW);
				ConsolePuts(stateNames[systemState->name],YELLOW);
				ConsolePuts(" -> ",YELLOW);
				ConsolePuts(stateNames[newState->name],YELLOW);
				ConsolePuts(" [OK]\r\n",YELLOW);

				systemState->onExit(NULL);
				systemState = newState;
				systemState->onEntry(NULL);

			}else{

				ConsolePuts("STATE TRANSISTION ",RED);
				ConsolePuts(stateNames[systemState->name],RED);
				ConsolePuts(" -> ",RED);
				ConsolePuts(stateNames[newState->name],RED);
				ConsolePuts(" [ERROR]\r\n",RED);
				while(1);
			}
		}
	}
}

void AppMain(void) {
	extern State_t State_Init;

	xTaskCreate(SystemController, ( signed char * ) "System Controller", 1000, ( void * ) &State_Init, 3, NULL );
	vTaskStartScheduler();

	for(;;);
}
