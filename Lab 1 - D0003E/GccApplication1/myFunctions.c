/*
	All the necessary functions
*/
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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
		if (ch >= '0' || ch <= '9'){
			
			int pair = pos / 2;					      // Make sure it's either pair 0,1 - 2,3 or 4,5
			int lr;								      // left or right
			
			char lcddr = 0xEC;						  // Register position for LCDDR0 is 0xEC
			#define lcdReg _SFR_MEM8(lcddr + pair)    // Register position for LCDDR0 + 0,1 or 2 to determine whether it's LCCDR0, LCCDR1 or LCDDR2 we are going to print in
		
			// All the numbers
			// 0 - 0x1551, 1 - 0x0110, 2 - 0x1E11, 3 - 0x1B11, 4 - 0x0B50, 5 - 0x1B41, 6 - 0x1F41, 7 - 0x0111, 8 - 0x1F51, 9 - 0x0B51
			uint16_t scc[10] = {0x1551, 0x0110, 0x1E11, 0x1B11, 0x0B50, 0x1B41, 0x1F41, 0x0111, 0x1F51, 0x0B51};
			
			// Check if we want 
			
			if (pos % 2 == 0){
				lr = 0xF0;
			}
		
			else {
				lr = 0xF;
			}
			
			uint16_t num = scc[ch - '0'];
			
			for (int i = 0; i < 4; i++) {
				int nibble = num & 0xF;
				num = num >> 4;
				
				if(pos % 2 != 0) {
					nibble = nibble << 4;
				}
				
				lcdReg = (lcdReg & lr) | nibble;
				lcddr += 5;
			}
		}
	}
	
	else{
		return;
	}
}

void writeLong(long i){
	for (int n = 5; n >= 0; n--) {
		char ch = (i % 10) + '0';
		i /= 10;
		writeChar(ch, n);
	}
}

void prime(){
	for(long i = 2; i <= 999; i++){
		if(is_prime(i)){
			writeLong(i);
			
		}
	}
}

int is_prime(long i){
	for(int n = 2; n < i; n++){
		if(i % n == 0){
			return(0);
		}
	}
	return(1);
}

void blink(){
	TCCR1B = (1 << CS12);
	
	uint16_t clk = 0;
	uint16_t interval = 8000000/256;
	int on = 0;
	bool overflowflag = false;  //ska vi använda??
	
	while(1){
		if(TCNT1 == clk && !overflowflag){
			clk = TCNT1 + interval;
			if(on == 0){
				LCDDR0 = 0x2;
				on = 1;
			}else{
				LCDDR0 = 0x0;
				on = 0;
			}
		}
			
		if (TCNT1 < 0xFFFF){
				overflowflag = false;
		}else{
			overflowflag = true;
			
			clk = TCNT1 + interval;
		}
	}
}

void button(){
	
	PORTB = (1 << PB7);//0b10000000;
	
	LCDDR8 = 0x1;
	LCDDR13 = 0x0;
	//bool pressingflag = false;
	
	while(1){
		if(PINB7 == 0x0){
			LCDDR13 = 0x0;
			//pressingflag = true;
			
		}else{
			LCDDR13 = 0x1;
		}
	}
}