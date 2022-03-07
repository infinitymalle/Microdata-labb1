#ifndef _GUI_h
#define _GUI_h
#include "PulseGenerator.h"

#define initGUI(pulsegen1, pulsegen2, foc) {initObject(), {pulsegen1, pulsegen2}, foc};

typedef struct {
	Object super;
	Pulsegen *pg[2];
	int focus;
} GUI;

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);
void updatedisplay(GUI *self);
void changefocus(GUI *self, int newfocus);
void inc(GUI *self);
void dec(GUI *self);
void yoholdon(GUI *self);
#endif