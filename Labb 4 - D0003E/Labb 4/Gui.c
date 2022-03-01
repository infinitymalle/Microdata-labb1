#include "GUI.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void button();

void LCD_Init(void)
{
	/*
		LCD Control and Status Register:
		LCDCS    - Asynchronous clock source
		LCDMUX's - Duty = 1/4, Bias = 1/3
		LCDPM's  - Number of Segments = 25
	*/
	
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	
	/*
		LCD Frame Rate Register:
		LCDCD's - Prescaler setting N = 16
	*/
	
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	
	/*
		LCD Contrast Control Register
		None of the LCDDC's used = 300 microseconds
		LCDCC's = 3,35V
	*/
	
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	
	/*
		LCDEN = LCD Enabled
		LCDAB = Low Power Waveform
	*/
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	
	// start joystick
	//DDRB = 0b11010000;								//För att tillåta sättningen av bitarna (Tror vi :))
	//EIFR = (1 << PCIF0) | (1 << PCIF1);
	DDRE   = (1<<DDE6) | (1<<DDE4);
	EIMSK = (1 << PCIE1) | (1 << PCIE0);
	/*
		Joystick up
	*/
	PCMSK1 = (1 << PCINT14);
	PORTB = (1 << PB6);
	
	/*
		Joystick down
	*/
	PCMSK1 = (1 << PCINT15);
	PORTB = (1 << PB7);
	
	/*
		Joystick right
	*/
	PCMSK0 = (1 << PCINT3);
	PORTE = (1 << PE3);
	
	/*
		Joystick left
	*/
	PCMSK0 =  (1 << PCINT2);
	PORTE =  (1 << PE2);
	
	/*
		Joystick press
	*/
	PCMSK1 = (1 << PCINT12);
	PORTB = (1 << PB4);
	
	//EMIF = (1 << PCIF1) | (1 << PCIF0);
	
	
	printAt(0, '0');
	printAt(0, '1');
	printAt(0, '4');
	printAt(0, '5');
	button();
}

void printAt(long num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

void writeChar(char ch, int pos)
{
	// All the numbers
	// 0 - 0x1551, 1 - 0x0110, 2 - 0x1E11, 3 - 0x1B11, 4 - 0x0B50, 5 - 0x1B41, 6 - 0x1F41, 7 - 0x0111, 8 - 0x1F51, 9 - 0x0B51
	uint16_t scc[] = {0x1551, 0x0110, 0x1E11, 0x1B11, 0x0B50, 0x1B41, 0x1F41, 0x0111, 0x1F51, 0x0B51};
	
	if(pos >= 0 && pos <= 5){
		if (ch >= '0' || ch <= '9'){
			int pair = pos / 2;					      // Make sure it's either pair 0,1 - 2,3 or 4,5
			uint8_t *lcddr = (uint8_t *) 0xEC + pair; // Point to register position 0xEC which is LCDDR0 and add pair to get LCDDR0, LCDDR1 or LCDDR2
			uint16_t num = scc[ch - '0'];			  // Get the hexadecimal number from the list

			for (int i = 0; i <= 3; i++) {			  // Loop through every number in the hexadecimal number
				int nibble = num & 0xF;				  // Get the least significant number in the hex
				
				if(pos % 2 == 1) {				      // Check if the nibble parts should be in the left or right number in the pair
					nibble *= 0x10;					  // If pos % 2 == 1 -> nibble will load in right digit
					*lcddr = *lcddr & 0xF;
				}
				
				else {
					*lcddr = *lcddr & 0xF0;
				}
				
				*lcddr = *lcddr | nibble;			  // Write the nibble to the digit
				lcddr += 5;							  // Go to LCDDRx + 5
				num /= 0x10;						  // Next nibble
			}
		}
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




