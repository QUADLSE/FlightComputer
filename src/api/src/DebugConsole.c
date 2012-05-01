#include "DebugConsole.h"
#include "qCOMMS.h"
#include "string.h"

static const char * colorArray[]={COLOR_BLACK,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,COLOR_MAGENTA,COLOR_MAGENTA,COLOR_CYAN,COLOR_WHITE};

void ConsolePuts(char * buff,int color ){

	uint8_t * msgs[] = {(uint8_t *)(colorArray[color]),(uint8_t *)buff};
	uint8_t sz[] = {strlen((char*)colorArray[color]),strlen((char*)buff)};

	qComms_SendCompoundMsg(UART_GROUND,0xAA,MSG_TYPE_DEBUG,sz,msgs,2);
}
