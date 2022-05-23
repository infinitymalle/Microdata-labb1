#include "GUI.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void general_Init(void)
{
	/*
		LCD Control and Status Register:
		LCDCS    - Asynchronous clock source
		LCDMUX's - Duty = 1/4, Bias = 1/3
		LCDPM's  - Number of Segments = 25
	*/
	
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0) | LCDCRB;
	
	/*
		LCD Frame Rate Register:
		LCDCD's - Prescaler setting N = 16
	*/
	
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0) | LCDFRR;
	
	/*
		LCD Contrast Control Register
		None of the LCDDC's used = 300 microseconds
		LCDCC's = 3,35V
	*/
	
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0) | LCDCCR;
	
	/*
		LCDEN = LCD Enabled
		LCDAB = Low Power Waveform
	*/
	LCDCRA = (1 << LCDEN) | (1 << LCDAB) | LCDCRA;
	
	LCDDR8 = 1;
	printAt(0, 0);
	printAt(0, 2);
	printAt(0, 4);
	
	USART_Init();
	
}

void USART_Init(){
	
	#define FOCS 8000000
	#define BAUD 9600
	#define MYUBRR (FOCS/16/BAUD-1)
	
	UBRR0H = (unsigned char) (MYUBRR>>8);
	UBRR0L = (unsigned char) MYUBRR;
	
	UCSR0B = (1 << TXEN0) | (1 << RXCIE0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void printAt(long num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

void writeChar(char ch, int pos){
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
					if(lcddr == &LCDDR0){
						*lcddr = *lcddr & 0xD;
					}
					else{
						*lcddr = *lcddr & 0xF;
					}
					}else{
					if(lcddr == &LCDDR0){
						*lcddr = *lcddr & 0xD0;
						}else{
						*lcddr = *lcddr & 0xF0;
					}
				}
				
				*lcddr = *lcddr | nibble;			  // Write the nibble to the digit
				lcddr += 5;							  // Go to LCDDRx + 5
				num /= 0x10;						  // Next nibble
			}
		}
	}
}


void setleft(GUI *self, int val){  //South
	printAt(val, 0);
}
void setmiddle(GUI *self, int val){ //Cars on bridge
	printAt(val, 2);
}
void setright(GUI *self, int val){ //North
	printAt(val, 4);
}