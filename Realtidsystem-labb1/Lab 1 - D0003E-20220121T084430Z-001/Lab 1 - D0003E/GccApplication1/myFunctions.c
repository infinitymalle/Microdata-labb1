/*
	All the necessary functions
*/
#include <avr/io.h>
#include <stdlib.h>

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
	if(pos >= 0 && pos <= 5){
		int pair = pos / 2;							// Make sure it's either pair 0,1 - 2,3 or 4,5
		int lr = 1;
		
		if (pos % 2 == 0) {
			lr = 1;	
		}
		else{
			lr = 16;
		}
		
		char lcddr = 0xEC;
		#define lcdReg _SFR_MEM8(lcddr + pair)    // Register position for LCDDR0 + 0,1 or 2 to determine whether it's LCCDR0, LCCDR1 or LCDDR2 we are going to print in
		
	
		// All the numbers
		// 0 - 0x1551 - 0x15510000, 1 - 0x0110 - 0x01100000, 2 - 0x1E11 - 0x1E110000, 3 - 0x1B11 - 0x1B110000, 4 - 0x0B50 - 0x0B500000, 5 - 0x1B41 - 0x1B410000, 6 - 0x1F41 - 0x1F410000, 7 - 0x0111 - 0x01110000, 8 - 0x1F51 - 0x1F510000, 9 - 0x0B51 - 0x0B510000
		
		if (ch >= 0 || ch <= 9){
			
			switch (ch)
			{
				case '0':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x5 * lr;
					lcddr += 5;
					lcdReg = 0x5 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '1':
					lcdReg = 0x0 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x0 * lr;
				break;
				
				case '2':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0xE * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '3':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0xB * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '4':
					lcdReg = 0x0 * lr;
					lcddr += 5;
					lcdReg = 0x5 * lr;
					lcddr += 5;
					lcdReg = 0xB * lr;
					lcddr += 5;
					lcdReg = 0x0 * lr;
				break;
				
				case '5':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x4 * lr;
					lcddr += 5;
					lcdReg = 0xB * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '6':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x4 * lr;
					lcddr += 5;
					lcdReg = 0xF * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '7':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x0 * lr;
				break;
				
				case '8':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x5 * lr;
					lcddr += 5;
					lcdReg = 0xF * lr;
					lcddr += 5;
					lcdReg = 0x1 * lr;
				break;
				
				case '9':
					lcdReg = 0x1 * lr;
					lcddr += 5;
					lcdReg = 0x5 * lr;
					lcddr += 5;
					lcdReg = 0xB * lr;
					lcddr += 5;
					lcdReg = 0x0 * lr;
				break;
				
			}
		}
	}
	
	else{
		return;
	}
}

void writelong(long i){
	
}