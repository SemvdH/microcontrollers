/*
 * main.c
 *
 * Created: 10-Feb-21 9:13:02 AM
 *  Author: lemms
 */ 

# define F_CPU 10000000UL

#include <util/delay.h>
#include <avr/io.h>

typedef enum {
	false = 0,
	true = 1
} bool;

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of milliseconds
inputs:			int ms (Number of milliseconds to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	bool dir = false;
	DDRD = 0b11111111;
	PORTD = 0b00000001;
	
    while(1)
    {
        if(PORTD == 0b10000000){
			dir = true;
		}
		
		if(PORTD == 0b00000001){
			dir = false;
		}
		
		if(!dir){
			PORTD <<= 1;
		} else {
			PORTD >>= 1;	
		}
		
		wait(80);
    }
}
