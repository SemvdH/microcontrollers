/*
 * main.c
 *
 * Created: 11-Feb-21 11:01:07 PM
 *  Author: lemms
 */ 


#define F_CPU 10e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_control.h"


int main(void)
{
	
	init_4bits_mode();
	
		
	_delay_ms(10);
	
	lcd_clear();
		
	lcd_write_string("Pintebaas");
	
    while(1)
    {
	
        //TODO:: Please write your application code 
    }
}

