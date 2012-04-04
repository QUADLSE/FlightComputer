/*
 * SystemConfig.c
 *
 *  Created on: Mar 6, 2012
 *      Author: Alan
 */

#include "Config.h"

SystemConfig_t System={OFF,ON};


void DebugConsolePuts(char * buff, int color){
	if (System.DebugConsole == ON){
		ConsolePuts(buff,color);
	}
}
