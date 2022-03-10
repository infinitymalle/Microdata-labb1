#include <avr/io.h>
#include <avr/iom169p.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"

void button_Init(){								
	
	/*
		Aktiverar PORTE pin 4 samt 6 för output
	*/
	DDRE  = (1 << DDE6) | (1 << DDE4) | DDRE;
	
	/*
		Button interupt
	*/
	EIMSK = (1 << PCIE1) | (1 << PCIE0) | EIMSK;
	/*
		Joystick up
	*/
	PCMSK1 = (1 << PCINT14) | PCMSK1;
	PORTB = (1 << PB6) | PORTB;
	
	/*
		Joystick down
	*/
	PCMSK1 = (1 << PCINT15) | PCMSK1;
	PORTB = (1 << PB7) | PORTB;
	
	/*
		Joystick right
	*/
	PCMSK0 = (1 << PCINT3) | PCMSK0;
	PORTE = (1 << PE3) | PORTE;
	
	/*
		Joystick left
	*/
	PCMSK0 =  (1 << PCINT2) | PCMSK0;
	PORTE =  (1 << PE2) | PORTE;
	
	/*
		Joystick press
	*/
	PCMSK1 = (1 << PCINT12) | PCMSK1;
	PORTB = (1 << PB4) | PORTB;
}

void direction(Joystick *self){
	if (((PINB >> 7) & 1) == 0){
		ASYNC(self->gui, firstDec, NULL);
	}
	else if (((PINB >> 6) & 1) == 0){
		ASYNC(self->gui, firstInc, NULL);
	}
	else if(((PINB >> 4) & 1) == 0){
		ASYNC(self->gui->pg[self->gui->focus], stored, NULL);
	}
	ASYNC(self->gui, updatedisplay, 0);
}

void changepulsegenerator(Joystick *self){
	if(((PINE >> 2) & 1) == 0){
		ASYNC(self->gui, changefocus, 1);	
	}
	
	else if(((PINE >> 3) & 1) == 0){
		ASYNC(self->gui, changefocus, 0);
	}
}
