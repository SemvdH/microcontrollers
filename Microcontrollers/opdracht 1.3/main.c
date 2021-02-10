/*
 * opdracht 1.3.c
 *
 * Created: 10-2-2021 09:28:10
 * Author : Sem
 */ 

#include <avr/io.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0b11111111; // d is output
	DDRC = 0b00000000; // c is all input
    
    while (1) 
    {
		if (PINC & 0b00000001) {
			
			PORTD = 0b01000000;
			wait(1000);
			PORTD = 0b00000000;
			wait(1000);
		}
    }
}

