/*
 * opdracht 4.b1.c
 *
 * Created: 3-3-2021 10:54:49
 * Author : Sem
 */ 

/************************************************************************/
/* Verander het programma (voor kanaal 3 en voor 8 bits) zodat het alleen een AD-conversie uitvoert
als jij dat wilt, dus op aanvraag. Maak daarvoor in main() een eindeloze lus met een wachtfunctie
en een start voor de ADC (Zie ook code in de repository).                                                                     */
/************************************************************************/


#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), no free running
void adcInit( void )
{
	sei();						// enable interrupts
	ADMUX = 0b01100011;			// AREF=VCC, result left adjusted, channel3 at pin PF3
	ADCSRA = 0b10001110;		// ADC-enable, start conversion mode, no free running, interrupt enable 
}

/************************************************************************/
/* starts AD converstion by setting bit 6 in ADCSRA to 1                */
/************************************************************************/
void startConversion(void) {
	ADCSRA |= BIT(6);
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	DDRB = 0xFF;				// set PORTB for output
	adcInit();					// initialize ADC

	while (1)
	{
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;
		
		startConversion();
		wait(100);				// every 100 ms (busy waiting)
	}
}


