/*
 * timing.h
 *
 *  Created on: 15/10/2011
 *      Author: Alan
 */

#ifndef qTIMING_H_
#define qTIMING_H_

#include  <stdint.h>
typedef struct{
	uint32_t	startTime;
	uint32_t	endTime;
	uint32_t	ticksToSeconds;
	uint32_t	resolution;
}timerHnd;

void timerConfig(uint32_t resolution, timerHnd * t);
void timerStart(timerHnd * t);
void timerStop(timerHnd * t);
uint32_t timerGetElapsed(timerHnd * t);

#endif /* TIMING_H_ */
