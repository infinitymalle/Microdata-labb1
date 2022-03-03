#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"

void direction(){
	if (PINB >> 7 == 0){
		
	}
}

void button(){
	LCDDR8 = 1;
	LCDDR13 = 0;
	
	bool buttonPushed = false;
	volatile int i = 1;
	while(i){
		if (PINE >> 2 == 0 && !buttonPushed && LCDDR13 == 0x1){
			buttonPushed = true;
			LCDDR13 = 0;
			LCDDR8 = 1;
		}
		
		else if (PINE >> 2 == 0 && !buttonPushed && LCDDR8 == 0x1) {
			buttonPushed = true;
			LCDDR13 = 1;
			LCDDR8 = 0;
		}
		
		else if (PINE >> 2 == 1){
			buttonPushed = false;
		}
	}
}