#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Porthandler.h"
#include "GUI.h"

void changefocus(Pulse *self, int newfocus){
	self->focus = newfocus;
}
void updategui(Pulse *self){
	if(Pulse->focus == 1){
		ASYNC(self->GUI, updatedisplay,  );
	}
}

