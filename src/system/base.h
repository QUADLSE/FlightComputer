/*
 * system.h
 *
 *  Created on: Feb 1, 2012
 *      Author: Alan
 */

#ifndef TYPES_H_
#define TYPES_H_


typedef enum{
	RET_OK=0,
	RET_ERROR,
	RET_ALREADY_INIT,
	RET_MSG_OK,
	RET_MSG_ERROR,
	RET_MSG_BYTES_REMAINING
}ret_t;

typedef enum{
	DEVICE_NOT_READY = 0,
	DEVICE_READY
}status_t;

#endif /* TYPES_H_ */
