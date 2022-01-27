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
	//writeChar('6', 3);
	writeLong(1111800815);
	//prime();
	//blink();
<<<<<<< HEAD
	//button();
	//part4();
=======
	button();
>>>>>>> 852b5caa7680a3656aa5d4ad958a6739d0634f1d
}

