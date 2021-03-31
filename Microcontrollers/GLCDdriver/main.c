/*
 * GLCDdriver.c
 *
 * Created: 10-Mar-21 10:47:34 AM
 * Author : lemms
 */ 
#define F_CPU 10e6
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "stepper_driver.h"
	
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void adcInit(){
	ADMUX = 0b11100000; // internal reference: 2.56V and SEI on ADC0 and left-adjusted.
	ADCSRA = 0b10000110; // enable ADC. No free-run. Clock 64 D-factor.
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
    /* Replace with your application code */
	DDRF = 0x00;
	adcInit();
	init_stepper_driver();
	
	stepper_rotate(512);
    while (1) 
    {
		wait(100);
    }
}

