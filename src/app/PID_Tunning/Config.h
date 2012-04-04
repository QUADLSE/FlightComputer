/*
 * Config.h
 *
 *  Created on: Mar 6, 2012
 *      Author: Alan
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum{
	OFF=0,
	ON
} SettingStatus_t;

typedef struct {
	SettingStatus_t Telemetry;
	SettingStatus_t DebugConsole;
	// Estaria bueno agregar el modo del systema (estado)
} SystemConfig_t;

extern SystemConfig_t System;

void DebugConsolePuts(char * buff, int color);

#endif /* CONFIG_H_ */
