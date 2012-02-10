/***********************************************************************//**
 * @file		qTiming.h
 * @brief		Contains all macro definitions and function prototypes
 * 				for the TIMING driver.
 * @version
 * @date
 * @author
 *************************************************************************/
/** @ingroup BSP */
/** @addtogroup qTIMING */
/*@{*/

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
