#include <avr/io.h>
#include <avr/iom169p.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Joystick.h"
//#include "TinyTimber.h"
//#include "PulseGenerator.h"
//#include "Porthandler.h"

void direction(Joystick *self){
	if (PINB >> 7 == 0){
		if(self->pulse->focus == 1){
			AFTER(MSEC(400), self->pulse->pulse1, decrease, 0);
		}else{
			AFTER(MSEC(400), self->pulse->pulse2, decrease, 0);
		}
	}
	
	else if (PINB >> 6 == 0){
		if(self->pulse->focus == 1){
			AFTER(MSEC(400), self->pulse->pulse1, increase, 0);
		}else{
			AFTER(MSEC(400), self->pulse->pulse2, increase, 0);
		}
	}
	
	else if(PINB >> 4 == 0){
		if(self->pulse->focus == 1){
			ASYNC(self->pulse->pulse1, stored, 0);
		}else{
			ASYNC(self->pulse->pulse2, stored, 0);
		}
	}
	
	ASYNC(self->pulse, updategui, 0);
}
void changepulsegenerator(Joystick *self){
	if(PINE >> 2 == 0){
		ASYNC(self->pulse, changefocus, 1);	
	}
	
	else if(PINE >> 3 == 0){
		ASYNC(self->pulse, changefocus, 0);
	}
}