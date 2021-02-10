/*
 * main.c
 *
 * Created: 2/10/2021 11:45:42 AM
 *  Author: Sem
 */ 
#include <avr/interrupt.h>
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int count;
/************************************************************************/
/* interrupt 1
walk the light 1 down                                                                     */
/************************************************************************/
ISR( INT0_vect ) {
	
	setDisplay(++count);
}

/************************************************************************/
/* interrupt 2
walk the light 1 up                                                                     */
/************************************************************************/
ISR( INT1_vect ) {
	
	setDisplay(--count);
}

const unsigned char Characters [15] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
};

void initDisplay(){
	DDRA = 0b11111111;
}

void setDisplay(int num){
	if(num > 15 || num < 0)
		num = 14;
		
	PORTA = Characters[num];
}

int main(void)
{
	initDisplay();
	setDisplay(0);
	
	/* Replace with your application code */
	
	// Init I/O
	DDRD = 0b00000000;
	
	// Init Interrupt hardware
	EICRA |= 0b00001010;			// INT2 falling edge, INT1 rising edge
	EIMSK |= 0b00000011;			// Enable INT1 & INT0
	
	PORTC = 0x01; // init the first bit
	
	sei(); // enable input mechanism
	
    while(1)
    {
        if((PIND == 0b00000011) && (count != 0)){
	        count = 0;
			setDisplay(count);
        }
    }
}
