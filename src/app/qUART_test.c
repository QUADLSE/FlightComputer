/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#include "base.h"
#include "qUART.h"
#include "string.h"


uint8_t buff[]={"Hello world!"};

int AppMain(void) {
	//FIXME: Metodo!!!
	qUART[2].BaudRate = 115200;
	qUART[2].DataBits = 8;
	qUART[2].Parity = PARITY_NONE;
	qUART[2].StopBits = 1;

	if (qUART_Init(2)==RET_ERROR){
		while(1);
	};

	while(1) {
		int i;
		qUART_Send(2,buff,strlen(buff));
		for(i=0;i<1000000;i++);
	}
	return 0 ;
}
