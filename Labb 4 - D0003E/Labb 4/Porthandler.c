#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Porthandler.h"

void changefocus(Pulse *self, int newfocus){
	self->focus = newfocus;
}
void updategui(Pulse *self){
	if(self->focus == 1){
		ASYNC(self->gui, updatedisplay, self->pulse1->currentFreq);
	}else{
		ASYNC(self->gui, updatedisplay, self->pulse2->currentFreq);
	}
}

