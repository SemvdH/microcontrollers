/*
 * counter_t2_interrupt.c
 *
 * Created: 21/02/2021 13:00:25
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_control.h"

#define BIT(x)			(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

char * toArray(int number)
{
	int n = log10(number) + 1;
	int i;
	char *numberArray = calloc(n, sizeof(char));
	for (i = n-1; i >= 0; --i, number /= 10)
	{
		numberArray[i] = (number % 10) + '0';
	}
	return numberArray;
}

int TimerPreset = -1;  // 0xF6, 10 till overflow
int number = 0;

// Interrupt routine timer2 overflow
ISR( TIMER2_OVF_vect ) {
	TCNT2 = TimerPreset;	// Preset value
	number++;		// Increment counter
	lcd_clear();
	
	int length = snprintf(NULL, 0, "%d", number + 1);
	char str[length + 1];
	snprintf(str, length + 1, "%d", number + 1);
	lcd_write_string(str);
}

// Initialize timer2
void timer2Init( void ) {
	TCNT2 = TimerPreset;	// Preset value of counter 2
	TIMSK |= BIT(6);		// T2 overflow interrupt enable
	sei();				// turn_on intr all
	TCCR2 = 0x07;		// Initialize T2: ext.counting, rising edge, run
}

int main(void) {
	
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	DDRA = 0xFF;			// set PORTA for output (shows countregister)
	DDRB = 0xFF;			// set PORTB for output (shows tenthvalue)
	
	init_4bits_mode();
	_delay_ms(10);
	
	lcd_clear();
	
	lcd_write_string("yeet");
	
	timer2Init();

	while (1) {
		PORTA = TCNT2;		// show value counter 2
		PORTB = number;	// show value tenth counter
		wait(10);
	}
}