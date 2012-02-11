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

/** Struct for holding timer data */
typedef struct{
	uint32_t	startTime;			/**< Tick count at the moment that the chrono started */
	uint32_t	endTime;			/**< Tick count at the moment that the chrono stopped */
	uint32_t	ticksToSeconds;		/**< Tick conversion rate to seconds*/
	uint32_t	resolution;			/**< Timer resolution */
}timerHnd;

void timerConfig(uint32_t resolution, timerHnd * t);
void timerStart(timerHnd * t);
void timerStop(timerHnd * t);
uint32_t timerGetElapsed(timerHnd * t);

#endif /* TIMING_H_ */
/*@}*/
/*@}*/
