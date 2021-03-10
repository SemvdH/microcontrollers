/*
 * opdracht 4.1.c
 *
 * Created: 03-Mar-21 9:26:31 AM
 * Author : lemms
 */ 


#define F_CPU 8e6
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_control.h"
#define BIT(x)			(1 << (x))

void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void adcInit(){
	ADMUX = 0b11100000; // internal reference: 2.56V and SEI on ADC0 and left-adjusted.
	ADCSRA = 0b10000110; // enable ADC. No free-run. Clock 64 D-factor.
}

void timer2Init( void ) {
	TIMSK |= BIT(7);		// T2 compare match interrupt enable
	sei();					// turn_on interrupt all
	TCCR2 = 0b00000011;		// Initialize T2: timer, pre-scaler=64
}

ISR( TIMER2_COMP_vect ) {
	ADCSRA |= BIT(6);
}

int getADCValue(){
	int value = 0;
	value = ADCH;
	value <<= 2;
	value += (ADCL >> 6);
	return value;
}



int main(void)
{
	int previousValue = 0;
    /* Replace with your application code */
	DDRF = 0x00; // set port F input.
	DDRE = 0xFF; // all port A output.
	adcInit();
	
	init_4bits_mode();
	_delay_ms(10);
	lcd_clear();

	timer2Init();
    while (1) 
    {
		PORTD = ADCH;
		PORTE = ADCL;
		
		int number = ADCH;

		if(previousValue != number){
			
			lcd_clear();
			
			wait(10);
			
			lcd_write_integer(getADCValue());
		}
		
		previousValue = number;
		
		wait(100);
    }
}

