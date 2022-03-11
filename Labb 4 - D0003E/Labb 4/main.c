#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"

int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
	button_Init();
	LCD_Init();
	
	Writer writer = initWriter();
	Pulsegen pg[2] = {initPulsegen(0, 0, 4, 0, &writer), initPulsegen(0, 0, 6, 0, &writer)};
	GUI gui = initGUI(pg, pg+1, 1, 0);		// +1 för nästa element
	
	Joystick joystick = initJoystick(&gui);
	
	INSTALL(&joystick, changepulsegenerator, IRQ_PCINT0);
	INSTALL(&joystick, direction, IRQ_PCINT1);
	
	return TINYTIMBER(joystick.gui, updatedisplay, NULL);
}

