#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "Gui.h"
#include "Porthandler.h"
#include "Pulsegenerator.h"
#include "Joystick.h"



int main(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    //LCD_Init();
	
	GUI gui = initGUI();
	Pulsegen pulse1 = initPulsegen(0, 0);
	Pulsegen pulse2 = initPulsegen(0, 0);
	Pulse pulse = initPulse(1, &pulse1, &pulse2, &gui);
	Joystick joystick = initJoystick(&pulse);
	
	INSTALL(&joystick, direction, IRQ_PCINT0);
	INSTALL(&joystick, direction, IRQ_PCINT1);
	
	return TINYTIMBER(&joystick, LCD_Init, NULL);
}

