#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Porthandler.h"
//#include "GUI.h"

void changefocus(Pulse *self, int newfocus){
	self->focus = newfocus;
}
void updategui(Pulse *self){
	if(self->focus == 1){
		ASYNC(self->gui, updatedisplay, 0);
	}else{
		ASYNC(self->gui, updatedisplay, 4);
	}
}

