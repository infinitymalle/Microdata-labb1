/*
 * GccApplication1.c
 *
 * Created: 2022-01-20 13:11:46
 * Author : Shorty, Malkolm Lundkvist
 */ 

#include <avr/io.h>
#include "myFunctionsInclude.h"

int main(void)
{
    CLKPR = 0x80;
	CLKPR = 0x00;
	LCD_Init();
	char ch = '9';
	int i = 3;
	writeChar(ch, i);
	
}

