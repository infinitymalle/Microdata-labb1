/*
 * Labb 5.c
 *
 * Created: 2022-03-10 09:54:03
 * Author : Malkolm Lundkvist & Eddie Höglund
 */ 

#include <avr/io.h>
#include "Inputs.h"

int main(void){
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	GUI gui = initGUI();
	Outputs outputs = initOutputs();
	Bridge bridge = initBridge(0, 0, 0, 0, 0, 0, &gui);
	Inputs input = initInputs(&bridge);
	
	INSTALL(&input, newcar, IRQ_USART0_RX);
	
	return TINYTIMBER(&gui, LCD_Init, NULL);
}


