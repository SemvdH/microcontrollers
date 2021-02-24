/*
 * timer_t2_ms.c
 *
 * Created: 21/02/2021 13:20:32
 * Author : Etienne
 */ 

#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

volatile int msCount = 0;

void timer2Init( void ) {
	OCR2 = 150; //155				// Compare value of counter 2
	TIMSK |= BIT(7);		// T2 compare match interrupt enable
	sei();					// turn_on intr all
	TCCR2 = 0b00001101;		// Initialize T2: timer, prescaler=32, compare output disconnected,CTC,RUN
}
unsigned int msThersh = 15;

ISR( TIMER2_COMP_vect ) {
		PORTC ^= BIT(0);
		if(OCR2 == 250){
			OCR2 = 150;	
		} else {
			OCR2 = 250;
		}
		
}

int main( void ) {
	DDRC = 0xFF;
	PORTC = BIT(0);				// set PORTC for output (toggle PC0)
	timer2Init();

	while (1) {
		// do something else
		wait(10);			// every 10 ms (busy waiting
	}
}