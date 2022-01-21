/*
	All the necessary functions
*/
#include <avr/io.h>

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
}

void writeChar(char ch, int pos)
{
	//LCDDR0 = 0x5;
	LCDDR5 = 0x5;
	LCDDR10 = 0xF;
	LCDDR15 = 0x0;
	LCDDR1 = 0x1;
	LCDDR6 = 0x5;
	LCDDR11 = 0xF;
	LCDDR16 = 0x0;
	LCDDR8 = 0x1;
	LCDDR13 = 0x1;
	if(pos >= 0 && pos <= 5){
		
		
	}
}
void writelong(long i){
	
}