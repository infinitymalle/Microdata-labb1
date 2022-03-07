#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "pinwriter.h"
//
//
//
void write(Writer *self){
          *USCK = freq;
          *DO = freq;
}

// https://dtsheet.com/doc/1815614/view-detail-for-avr-butterfly-evaluation-kit---user-guide
//Pin 1 (USCK/SCL) PORTE bit 4
//Pin 3 (DO)       PORTE bit 6
//Pin 4 (GND)
