/*
 * States.c
 *
 *  Created on: Apr 3, 2012
 *      Author: Alan
 */

#include "States.h"

const transition_t	/* 		|  STATE_INIT  | 	STATE_IDLE  |	STATE_FLIGHT_MANUAL	|	STATE_FLIGHT_TUNNING 	|	STATE_FLIGHT_RUNNING |*/
transitionTable[5][5]={
/*	STATE_INIT			*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*	STATE_IDLE			*/{		NO,					NO,					YES,					YES,					 	YES				}	,
/*	STATE_FLIGHT_MANUAL	*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*	STATE_FLIGHT_TUNNING*/{		NO,					YES,				NO,						NO,					 		NO				}	,
/*	STATE_FLIGHT_RUNNING*/{		NO,					YES,				NO,						NO,					 		NO				}	};

