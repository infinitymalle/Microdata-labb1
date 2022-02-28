#include <TinyTimber.h>
#include <TinyTimber.c>
#include <Helpfile.h>
#include <Helpfile.c>
#include <avr/io.h>
#include <stdbool.h>

int main(void)
{
    
    CLKPR = 0x80;
    CLKPR = 0x00;
    LCD_Init();
}

