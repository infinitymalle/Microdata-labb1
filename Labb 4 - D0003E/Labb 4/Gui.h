#ifndef _GUI_h
#define _GUI_h

#define initGUI(left, right) {initObject(), 0, 1}
#include <stdbool.h>

typedef struct {
	Object super;
	bool left;
	bool right;
} GUI;

void LCD_Init();
void printAt(long num, int pos);
void writeChar(char ch, int pos);

#endif _GUI_h