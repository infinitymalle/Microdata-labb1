/*
 * GccApplication1.c
 *
 * Created: 2022-01-20 13:11:46
 * Author : Shorty, Malkolm Lundkvist
 */ 

#include <avr/io.h>
#include "myFunctionsInclude.h"
#include <math.h>

int main(void)
{
    CLKPR = 0x80;
	CLKPR = 0x00;
	LCD_Init();
	//writeChar('6', 0);
	//writeLong(1111800815);
	//prime();
	blink();
}

