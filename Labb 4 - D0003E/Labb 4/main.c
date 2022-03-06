#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"
#include "Gui.h"

int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
	button_Init();
	LCD_Init();
	
	Pulsegen pg[2] = {initPulsegen(0, 0), initPulsegen(0, 0)};
	GUI gui = initGUI(pg, pg+1, 1);		// +1 för nästa element
	//Pulse pulse = initPulse(&pulse1, &pulse2, &gui);
	
	Joystick joystick = initJoystick(&gui);
	
	INSTALL(&joystick, changepulsegenerator, IRQ_PCINT0);
	INSTALL(&joystick, direction, IRQ_PCINT1);
	
	return TINYTIMBER(joystick.gui, updatedisplay, NULL);
}

