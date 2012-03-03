/*
 * qFSM.h
 *
 *  Created on: Mar 3, 2012
 *      Author: Alan
 */

#ifndef QFSM_H_
#define QFSM_H_

typedef enum{
	NO=0,
	YES
}transition_t;

typedef enum{
	STATE_INIT=0,
	STATE_IDLE,
	STATE_FLIGHT_MANUAL,
	STATE_FLIGHT_TUNNING,
	STATE_FLIGHT_RUNNING,
	STATE_RESET
} system_states_t;

const char * stateNames[];

typedef struct{
	system_states_t name;
	void (*onEntry)(void *);
	void (*onExit)(void *);
} State_t;

#define TransitionValid(from,to,table) table[from][to]
void ChangeState(State_t * nextState);
/*
State_t State_Idle ={STATE_IDLE,Idle_onEntry,Idle_onExit};
State_t State_Flight_Manual ={STATE_FLIGHT_MANUAL,Fligth_Manual_onEntry,Fligth_Manual_onExit};
State_t State_Flight_Tunnning ={STATE_FLIGHT_TUNNING,Fligth_Tunning_onEntry,Fligth_Tunning_onExit};
State_t State_Flight_Running ={STATE_FLIGHT_RUNNING,Fligth_Running_onEntry,Fligth_Running_onExit};
*/
#endif /* QFSM_H_ */
