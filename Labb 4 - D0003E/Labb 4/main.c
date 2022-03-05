#include "TinyTimber.h"
#include <avr/io.h>
#include <stdbool.h>
#include "Gui.h"


int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    LCD_Init();
	GUI gui = initGUI();
	Joystick joystick = initJoystick();
	Pulse pulse = initPulse();
	
	INSTALL("", generatedPORTE, IRQ_PCINT0);
	INSTALL("", generatedPortB, IRQ_PCINT1);
	
	return TINYTIMBER();
}

