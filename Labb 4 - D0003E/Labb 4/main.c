#include <TinyTimber.h>
#include <Helpfile.h>
#include <avr/io.h>
#include <stdbool.h>
#include <GUI.h>


int main(void)
{
    
    CLKPR = 0x80;
    CLKPR = 0x00;
    LCD_Init();
	
}
