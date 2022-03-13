#include "Bridge.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void addcar(Bridge *self, int fromDirection){
	if (fromDirection == 0b0100){
		self->queueSouth++;
	}
	else if(fromDirection == 0b0001){
		self->queueNorth++;
	}
	else if(fromDirection == (0b1000 || 0b0010)){
		carRun(self);
	}
}

void changeDirection(Bridge *self){
	if (self->southLight){
		self->southLight = 0;
		AFTER(MSEC(5000), self, changeNorth, NULL);
	}else if (self->northLight){
		self->northLight = 0;
		AFTER(MSEC(5000), self, changeSouth, NULL);
	}
}

void carRun(Bridge *self){
	if((self->southLight == 1) && (self->queueSouth > 0)){			//left
		self->queueSouth--;
		self->carsOnBridge++;
		AFTER(MSEC(1000), self, carRun, NULL);
		AFTER(MSEC(5000), self, carLeave, NULL);
		self->carspassed++;
		if(self->carspassed >= 10){
			self->carspassed = 0;
			changeDirection(self);
		}
	}else if((self->northLight == 1) && (self->queueNorth > 0)){	//right
		self->queueNorth--;
		self->carsOnBridge++;
		AFTER(MSEC(1000), self, carRun, NULL);
		AFTER(MSEC(5000), self, carLeave, NULL);
		self->carspassed++;
		if(self->carspassed >= 10){
			self->carspassed = 0;
			changeDirection(self);
		}
	}
	updateDisp(self);
}

void carLeave(Bridge *self){
	if(self->carsOnBridge > 0){
		self->carsOnBridge--;
	}
}

void changeSouth(Bridge *self){
	self->southLight = 1;
	carRun(self);
}

void changeNorth(Bridge *self){
	self->northLight = 1;
	carRun(self);
}

void updateDisp(Bridge *self){
	ASYNC(self->gui, setleft, self->queueSouth);
	ASYNC(self->gui, setmiddle, self->carsOnBridge);
	ASYNC(self->gui, setright, self->queueNorth);
	ASYNC(self->outputs, transmit, self->northLight);
	//ASYNC(self->gui, updatedisplay, NULL);
};