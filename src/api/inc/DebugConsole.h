/*
 * DebugConsole.h
 *
 *  Created on: Feb 28, 2012
 *      Author: Alan
 */

#ifndef DEBUGCONSOLE_H_
#define DEBUGCONSOLE_H_

#include <stdint.h>
void ConsolePuts(const uint8_t * buff,int color );

#define ATTR_BASE	30
#define RESET		0
#define BRIGHT 		1
#define DIM			2
#define UNDERLINE 	3
#define BLINK		5
#define REVERSE		7
#define HIDDEN		8

#define COLOR_BASE_FG	30
#define COLOR_BASE_BG	40
#define BLACK 		0
#define RED			1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7


#endif /* DEBUGCONSOLE_H_ */
