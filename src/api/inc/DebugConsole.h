/*
 * DebugConsole.h
 *
 *  Created on: Feb 28, 2012
 *      Author: Alan
 */

#ifndef DEBUGCONSOLE_H_
#define DEBUGCONSOLE_H_

#include <stdint.h>
void ConsolePuts(char * buff,int color );

#define BLACK 		0
#define RED			1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

#define COLOR_BLACK			"\x1B[30m"
#define COLOR_RED			"\x1B[31m"
#define COLOR_GREEN			"\x1B[32m"
#define COLOR_YELLOW		"\x1B[33m"
#define COLOR_BLUE			"\x1B[34m"
#define COLOR_MAGENTA		"\x1B[35m"
#define COLOR_CYAN			"\x1B[36m"
#define	COLOR_WHITE			"\x1B[37m"

#endif /* DEBUGCONSOLE_H_ */
