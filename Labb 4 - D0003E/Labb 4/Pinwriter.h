#ifndef PINWRITER_H_
#define PINWRITER_H_
#include "TinyTimber.h"

#define initWriter() {initObject()}

typedef struct {
	Object super;
} Writer;

void togglepin(Writer *self, int pin);
void pinzero(Writer *self, int pin);

#endif