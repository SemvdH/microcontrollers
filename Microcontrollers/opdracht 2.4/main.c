/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

typedef struct {
	unsigned char data;
	unsigned int delay;
	} SEGMENT_DELAY;

SEGMENT_DELAY segments[] = {
	/* go around the outer layer twice */
	//	0		a			b			c			d			e			f
 	{0x00,100},{0x01,100},{0x02,100},{0x04,100},{0x08,100},{0x10,100},{0x20,100},{0x01,100},{0x02,100},{0x04,100},{0x08,100},{0x10,100},{0x20,100},
	/*	then fill it starting at a */	 
	{0x01,100},{0x03,100},{0x07,100},{0x0F,100},{0x1F,100},{0x3F,100},{0b00111110,100},{0b00111100,100},{0b00111000,100},{0b00110000,100},{0b00100000,100},
	/* blink the 3 horizontal bars 2 times from top to bottom*/
	{0x01,50},{0x00,50},{0x01,50},{0x00,50},{0x01,50},{0x00,50},{0x01,50},{0x00,50},
	{0b01000000,50},{0x00,50},{0b01000000,50},{0x00,50},{0b01000000,50},{0x00,50},{0b01000000,50},{0x00,50},
	{0x08,50},{0x00,50},{0x08,50},{0x00,50},{0x08,50},{0x00,50},{0x08,50},{0x00,50}
	/* go in a figure 8 pattern pattern*/
		 
};


/************************************************************************/
/* wait method
waits a specific amount of miliseconds                                                                     */
/************************************************************************/
void wait( int ms )

{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void )
{
	DDRA = 0xFF;
	
	
	while (1==1)
	{
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		for (int i = 0; i < sizeof(segments)/sizeof(segments[0]); i++)
		{
			// Write data to PORTA
			PORTA = segments[index].data;
			// wait
			wait(segments[index].delay);
			// increment for next round
			index++;
		}
	}
	/*we need to free the memory taken up by the array, otherwise it won't clear properly*/
	free(segments);

	return 1;
}