#ifndef _GUI_h
#define _GUI_h
#include "PulseGenerator.h"

#define initGUI(pulsegen1, pulsegen2, foc, buttonflag) {initObject(), {pulsegen1, pulsegen2}, foc, buttonflag};

typedef struct {
	Object super;
	Pulsegen *pg[2];
	int focus;
	int buttonflag;
} GUI;

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);
void updatedisplay(GUI *self);
void changefocus(GUI *self, int newfocus);
void inc(GUI *self);
void dec(GUI *self);
void resetbuttonflag(GUI *self);

void firstInc(GUI *self);
void firstDec(GUI *self);
#endif