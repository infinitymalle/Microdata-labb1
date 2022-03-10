#ifndef PINWRITER_H_
#define PINWRITER_H_
#include "TinyTimber.h"

#define initWriter(pin, freq, generateflag) {initObject(),pin, 0, 0}

typedef struct {
	Object super;
	int pin;
	int freq;
	int generateflag;

} Writer;

void generateFreq(Writer *self);
int getGenFlag(Writer *self);
void toggleGenFlag(Writer *self);
void setFreq(Writer *self, int newFreq);
#endif