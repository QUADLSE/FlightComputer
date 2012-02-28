#include "DebugConsole.h"
#include "qCOMMS.h"
#include "string.h"


static void textcolor(int color);

void ConsolePuts(const uint8_t * buff,int color ){

	//textcolor(color);
	qComms_SendMsg(UART_GROUND,0xAA,MSG_TYPE_DEBUG,strlen(buff)+1,buff);
	//textcolor(BLACK);
}

static void textcolor(int color)
{
	//const char Color_Green[] = {"\x1B[32m"};
	char command[10]={"\x1B[%%m"};
	command[2]=(COLOR_BASE_FG+color)/10+'0';
	command[3]=(COLOR_BASE_FG+color)%10+'0';
	qComms_SendMsg(UART_GROUND,0xAA,MSG_TYPE_DEBUG,strlen(command),command);

}
