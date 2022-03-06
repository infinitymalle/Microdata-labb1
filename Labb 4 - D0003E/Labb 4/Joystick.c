#include <avr/io.h>
#include <avr/iom169p.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"
//#include "TinyTimber.h"
//#include "PulseGenerator.h"
//#include "Porthandler.h"

void button_Init(){
	
	// start joystick
	//DDRB = 0b11010000;								//För att tillåta sättningen av bitarna (Tror vi :))
	//EIFR = (1 << PCIF0) | (1 << PCIF1);
	//DDRB  = (1 << DDB7) | (1 << DDB6) | (1 << DDB4) | DDRB;
	
	DDRE  = (1 << DDE6) | (1 << DDE4) | DDRE;		// Sätt portE pin 6 och 4 till output
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
		if(self->gui->focus == 1){
			ASYNC(self->gui->pg[0], decrease, NULL);
			//AFTER(MSEC(400), self->gui->pg[0], decrease, NULL);
		}else{
			ASYNC(self->gui->pg[1], decrease, NULL);
			//AFTER(MSEC(400), self->gui->pg[1], decrease, NULL);
		}
	}else if (((PINB >> 6) & 1) == 0){
		if(self->gui->focus == 1){
			ASYNC(self->gui->pg[0], increase, NULL);
			//AFTER(MSEC(400), self->gui->pg[0], increase, NULL);
		}else{
			ASYNC(self->gui->pg[1], increase, NULL);
			//AFTER(MSEC(400), self->gui->pg[1], increase, NULL);
		}
	}else if(((PINB >> 4) & 1) == 0){
		if(self->gui->focus == 1){
			ASYNC(self->gui->pg[0], stored, NULL);
		}else{
			ASYNC(self->gui->pg[1], stored, NULL);
		}
	}
	LCDDR8 = 0x1;
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